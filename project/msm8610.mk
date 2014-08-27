# top level project rules for the msm8610 project
#
LOCAL_DIR := $(GET_LOCAL_DIR)

TARGET := msm8610

MODULES += \
	app/tests \
	app/stringtests \
	app/shell \
	app/fastboot

ifeq ($(TARGET_BUILD_VARIANT),user)
DEBUG := 0
else
DEBUG := 1
endif

EMMC_BOOT := 1
ENABLE_SDHCI_SUPPORT := 1

#enable power on vibrator feature
ENABLE_PON_VIB_SUPPORT := true
ENABLE_PWM_SUPPORT := true

#GLOBAL_DEFINES += WITH_DEBUG_DCC=1
#GLOBAL_DEFINES += WITH_DEBUG_UART=1
GLOBAL_DEFINES += WITH_DEBUG_LOG_BUF=1
#GLOBAL_DEFINES += WITH_DEBUG_FBCON=1
GLOBAL_DEFINES += DEVICE_TREE=1
#GLOBAL_DEFINES += MMC_BOOT_BAM=1
#GLOBAL_DEFINES += CRYPTO_BAM=1
GLOBAL_DEFINES += ABOOT_IGNORE_BOOT_HEADER_ADDRS=1

GLOBAL_DEFINES += ABOOT_FORCE_KERNEL_ADDR=0x00008000
GLOBAL_DEFINES += ABOOT_FORCE_RAMDISK_ADDR=0x02000000
GLOBAL_DEFINES += ABOOT_FORCE_TAGS_ADDR=0x01e00000
GLOBAL_DEFINES += ABOOT_FORCE_KERNEL64_ADDR=0x00080000

#Disable thumb mode
#TODO: The gold linker has issues generating correct
#thumb interworking code for LK. Confirm that the issue
#is with the linker and file a bug report.
ENABLE_THUMB := false

ifeq ($(ENABLE_PON_VIB_SUPPORT),true)
GLOBAL_DEFINES += PON_VIB_SUPPORT=1
endif

ifeq ($(ENABLE_SDHCI_SUPPORT),1)
GLOBAL_DEFINES += MMC_SDHCI_SUPPORT=1
endif

ifeq ($(EMMC_BOOT),1)
GLOBAL_GLOBAL_DEFINES += _EMMC_BOOT=1
endif
