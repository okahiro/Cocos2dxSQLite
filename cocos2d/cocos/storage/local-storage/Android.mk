LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := cocos_localstorage_static

LOCAL_MODULE_FILENAME := liblocalstorage

LOCAL_SRC_FILES := LocalStorage.cpp


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../..

LOCAL_CFLAGS += -Wno-psabi
LOCAL_CFLAGS += -DSQLITE_HAS_CODEC
LOCAL_EXPORT_CFLAGS += -Wno-psabi

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_internal_static
LOCAL_WHOLE_STATIC_LIBRARIES += wxsqlite3_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,.)
$(call import-module,external/wxsqlite3)
