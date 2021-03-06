LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

GLOBAL_INCLUDES += \
	$(LOCAL_DIR)/include

GLOBAL_DEFINES += QCOM_ENABLE_DISPLAY

MODULE_DEPS += \
	dev/gcdb/display \
	dev/fbcon

MODULE_SRCS += \
	$(LOCAL_DIR)/target_display.c \
	$(LOCAL_DIR)/mipi_dsi.c \
	$(LOCAL_DIR)/mipi_dsi_phy.c \
	$(LOCAL_DIR)/display.c

ifeq ($(QCOM_DISPLAY_TYPE_MDP3),1)
GLOBAL_DEFINES += QCOM_DISPLAY_TYPE_MDP3
MODULE_SRCS += $(LOCAL_DIR)/mdp3.c
endif

ifeq ($(QCOM_DISPLAY_TYPE_MDP4),1)
GLOBAL_DEFINES += QCOM_DISPLAY_TYPE_MDP4
MODULE_SRCS += $(LOCAL_DIR)/mdp4.c
endif

ifeq ($(QCOM_DISPLAY_TYPE_MDP5),1)
GLOBAL_DEFINES += QCOM_DISPLAY_TYPE_MDP5
MODULE_SRCS += $(LOCAL_DIR)/mdp5.c
endif

ifeq ($(QCOM_DISPLAY_TYPE_MDSS),1)
GLOBAL_DEFINES += QCOM_DISPLAY_TYPE_MDSS
endif

ifeq ($(QCOM_DISPLAY_TYPE_MIPI),1)
GLOBAL_DEFINES += QCOM_DISPLAY_TYPE_MIPI
endif

include make/module.mk
