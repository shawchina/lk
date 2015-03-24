LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

ARCH := arm
ARM_CPU := cortex-a8
QCOM_ENABLE_EMMC := 1
QCOM_ENABLE_SDHCI := 1
QCOM_ENABLE_QTIMER := 1
QCOM_ENABLE_CLOCK_LIB2 := 1
QCOM_ENABLE_SPMI := 1

GLOBAL_INCLUDES += \
	$(LOCAL_DIR)/include

MODULE_SRCS += \
	$(LOCAL_DIR)/platform.c \
	$(LOCAL_DIR)/target.c \
	$(LOCAL_DIR)/acpuclock.c \
	$(LOCAL_DIR)/msm8610-clock.c \
	$(LOCAL_DIR)/gpio.c

MEMBASE := 0x0
MEMSIZE := 0x02000000	# 32MB
KERNEL_LOAD_OFFSET := 0x07A00000
LINUX_BASE := 0x0
LINUX_SIZE := 0x2c00000 # 44MB

MODULE_DEPS += \
	platform/qcom \
	dev/pmic/pm8x41

GLOBAL_DEFINES += \
	MEMBASE=$(MEMBASE) \
	MEMSIZE=$(MEMSIZE)

GLOBAL_CFLAGS += -DQCOM_ADDITIONAL_INCLUDE="<platform/msm8610.h>"

LINKER_SCRIPT += \
	$(BUILDDIR)/system-onesegment.ld

include make/module.mk
