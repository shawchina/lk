#include <err.h>
#include <pow2.h>
#include <debug.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <lib/bio.h>
#include <dev/keys.h>
#include <kernel/vm.h>
#include <kernel/thread.h>
#include <uefi/api.h>
#include <uefi/api_blockio.h>
#include <uefi/pe32.h>

#include "charset.h"

typedef void efi_entry_ptr(efi_handle_t, efi_system_table_t*);

typedef struct{
	efi_entry_ptr* entry;
	efi_handle_t image_handle;
} efiboot_request_t;

// efiboot thread
static int efiboot_thread_entry(void *arg)
{
	efiboot_request_t* req = arg;
	efi_entry_ptr* entry = req->entry;
	efi_handle_t image_handle = req->image_handle;
	free(req);

	dprintf(INFO, "Booting EFI binary...\n");

	// run binary
	entry(image_handle, &efi_system_table);

	return 0;
}

int peloader_load(bdev_t* kernel, bdev_t* ramdisk) {
	uint16_t i;
	const char* bootdev_name = NULL;
	const char* bootdev_label = NULL;
	const char* bootpath = GRUB_BOOT_PATH_PREFIX "/boot/grub/core.img";

	struct pe32_header __hdr;
	struct pe32_header* hdr = &__hdr;
	struct pe32_coff_header* coff = &hdr->coff_header;
	struct pe32_optional_header* opt = &hdr->optional_header;

	// read PE header
	if(bio_read(kernel, hdr, 0, sizeof(*hdr))!=(ssize_t)sizeof(*hdr)) {
		dprintf(CRITICAL, "Could not read PE header!");
		return ERR_NOT_VALID;
	}

	// check magic
	if(memcmp(hdr->signature, "PE\0\0", PE32_SIGNATURE_SIZE)) {
		return ERR_INVALID_ARGS;
	}
	// check machine type
	if(coff->machine!=PE32_MACHINE_ARMTHUMB_MIXED) {
		dprintf(CRITICAL, "Wrong machine type!");
		return ERR_NOT_VALID;
	}
	// check sections
	if(coff->num_sections!=4) {
		dprintf(CRITICAL, "Invalid number of sections!");
		return ERR_NOT_VALID;
	}
	// check optional header
	if(coff->optional_header_size!=sizeof(struct pe32_optional_header)) {
		dprintf(CRITICAL, "Unsupported optional header!");
		return ERR_NOT_VALID;
	}
	if(opt->magic!=PE32_PE32_MAGIC) {
		dprintf(CRITICAL, "Invalid optional header!");
		return ERR_NOT_VALID;
	}

	// allocate memory
	void* memory = pmm_alloc_map(opt->image_size, ARCH_MMU_FLAG_CACHED);
	if (!memory) {
		dprintf(CRITICAL, "Could not allocate memory!");
		return ERR_NO_MEMORY;
	}
	pmm_set_type_ptr(memory, VM_PAGE_TYPE_LOADER);
	uint32_t fixup_diff = (uint32_t)(memory - opt->image_base);

	// copy pe32 header
	// GRUB needs this to find the mod section
	if(bio_read(kernel, memory, 0, opt->header_size)!=(ssize_t)opt->header_size) {
		dprintf(CRITICAL, "Could not read header!");
		return ERR_NOT_VALID;
	}

	// read section table
	struct pe32_section_table sections[coff->num_sections];
	if(bio_read(kernel, sections, ((char*)(opt+1)) - (char*)hdr, sizeof(*sections)*coff->num_sections)!=(ssize_t)sizeof(*sections)*coff->num_sections) {
		dprintf(CRITICAL, "Could not read section table!");
		return ERR_NOT_VALID;
	}

	// load sections
	for(i=0; i<coff->num_sections; i++) {
		struct pe32_section_table* section = &sections[i];
		dprintf(SPEW, "section: %.8s virt:%x(%x) phys:%x(%x) rel:%x(%x) char:%x\n", section->name, section->virtual_address, section->virtual_size,
			section->raw_data_offset, section->raw_data_size, section->relocations_offset, section->num_relocations, section->characteristics);

		if(!(section->characteristics & PE32_SCN_MEM_DISCARDABLE)) {
			// read section into memory
			ASSERT(bio_read(kernel, memory+section->virtual_address, section->raw_data_offset, section->raw_data_size)==(ssize_t)section->raw_data_size);

			// zero out the remaining space
			if(section->virtual_size>section->raw_data_size)
				memset(memory+section->virtual_address+section->raw_data_size, 0, section->virtual_size-section->raw_data_size);
		}
	}

	// read relocation table
	void* relocation_table = malloc(opt->base_relocation_table.size);
	if(bio_read(kernel, relocation_table, opt->base_relocation_table.rva, opt->base_relocation_table.size)!=(ssize_t)opt->base_relocation_table.size) {
		dprintf(CRITICAL, "Could not read relocation table!");
		return ERR_NOT_VALID;
	}

	// relocate
	dprintf(INFO, "relocate to %p\n", memory);
	uint32_t fixup_offset = 0;
	while(fixup_offset<opt->base_relocation_table.size) {
		struct pe32_fixup_block* fixup = relocation_table + fixup_offset;
		uint32_t num_entries = (fixup->block_size-sizeof(*fixup))/sizeof(*fixup->entries);
		dprintf(SPEW, "reloc: page_rva=%x bs=%d items=%d\n", fixup->page_rva, fixup->block_size, num_entries);

		uint32_t i;
		for(i=0; i<num_entries; i++) {
			uint8_t type = fixup->entries[i]>>12;
			uint16_t offset = (fixup->entries[i]&0xFFF) + fixup->page_rva;

			switch(type) {
				case PE32_REL_BASED_HIGHLOW:
					*((uint32_t*)(memory+offset)) += fixup_diff;
				break;

				case PE32_REL_BASED_ABSOLUTE:
				break;

				default:
					PANIC_UNIMPLEMENTED;
				break;
			}
		}

		fixup_offset+=fixup->block_size;
	}
	free(relocation_table);

	// allocate boot-request and image-handle
	efiboot_request_t* req = malloc(1024*1024*10);
	req->entry = (efi_entry_ptr*)(memory + opt->entry_addr);
	req->image_handle = uefi_create_handle();

	// create EFI_LOADED_IMAGE protocol
	efi_loaded_image_t* li = calloc(1024*1024*10, 1);
	li->revision = 0x1000;
	li->parent_handle = NULL;
	li->system_table = &efi_system_table;
	li->device_handle = NULL;
	li->file_path = NULL;
	li->load_options_size = 0;
	li->load_options = NULL;
	li->image_base = memory;
	li->image_size = opt->image_size;
	li->image_code_type = 0; // TODO
	li->image_data_type = 0; // TODO
	li->unload = NULL; // TODO

	// ramdisk
	if(ramdisk) {
		// allocate memory for ramdisk
		void* ramdiskmem = malloc(ramdisk->size);
		ASSERT(ramdiskmem);

		// read ramdisk data
		if(bio_read(ramdisk, ramdiskmem, 0, ramdisk->size)!=(ssize_t)ramdisk->size) {
			dprintf(CRITICAL, "Could not read ramdisk!");
			return ERR_NOT_VALID;
		}

		// create public ramdisk device
		bootdev_name = "grub_ramdisk";
		create_membdev(bootdev_name, ramdiskmem, ramdisk->size, true);
	}
#ifdef GRUB_BOOT_PARTITION
	{
		bootdev_label = GRUB_BOOT_PARTITION;
	}
#endif

	// scan devices
	uefi_api_blockio_init();

	// set boot dev
	uefi_api_blockio_by_name(req->image_handle, bootdev_name, bootdev_label, &li->device_handle);
	DEBUG_ASSERT(li->device_handle);

	// create file path
	size_t pathlen = strlen(bootpath);

	// create device path interface
	efi_file_path_device_path_t* dp = uefi_create_device_path(sizeof(efi_file_path_device_path_t) + sizeof(uint16_t)*pathlen);
	dp->header.type = EFI_MEDIA_DEVICE_PATH_TYPE;
	dp->header.subtype = EFI_FILE_PATH_DEVICE_PATH_SUBTYPE;
	dp->header.length = sizeof(*dp) + sizeof(uint16_t)*pathlen;

	// convert name to utf16
	uint16_t* out = dp->path_name;
	const uint8_t* end;
	grub_utf8_to_utf16(out, pathlen, (const uint8_t *)bootpath, pathlen, &end);

	// set path
	li->file_path = (efi_device_path_t*)dp;

	// add loaded image protocol
	efi_guid_t guid = EFI_LOADED_IMAGE_GUID;
	uefi_add_protocol_interface(req->image_handle, guid, li);

	// clear pending keys
	keys_clear_all();

	// run binary in new thread
	thread_detach_and_resume(thread_create("efiboot", efiboot_thread_entry, (void*)req, DEFAULT_PRIORITY, EFI_STACK_SIZE));

	return NO_ERROR;
}
