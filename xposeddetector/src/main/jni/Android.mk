LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE            := xposed_detector
LOCAL_CFLAGS            := -Os
LOCAL_SRC_FILES         := xposed-detector.cpp
LOCAL_SRC_FILES         += xposed.cpp find-name.cpp
LOCAL_SRC_FILES         += classloader.cpp logging.cpp hash.cpp plt.c tinynew.cpp
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_EXPORT_LDLIBS     := -llog -ldl
# https://gist.github.com/vvb2060/56d5b8fda2553f36938b2b72b1390114
LOCAL_STATIC_OBJCOPY    := true
LOCAL_OBJCOPY_MODE      := --keep-global-symbol='get_xposed_status' --strip-unneeded -R .comment
include $(BUILD_STATIC_LIBRARY)
