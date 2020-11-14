LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE            := xposed_detector
LOCAL_CFLAGS            := -Oz
LOCAL_SRC_FILES         := xposed-detector.c
LOCAL_SRC_FILES         += xposed.c find-name.c
LOCAL_SRC_FILES         += classloader.cpp logging.c hash.c plt.c
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_LDLIBS            := -llog
# https://gist.github.com/vvb2060/56d5b8fda2553f36938b2b72b1390114
STATIC_LIBRARY_STRIP    := true
include $(BUILD_STATIC_LIBRARY)
