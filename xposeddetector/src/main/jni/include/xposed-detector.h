#pragma once

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
    // no xposed environment.
    NO_XPOSED,
    // have xposed environment but not hooked us,
    // or unknown xposed implementation, so hooks cannot be cleared.
    FOUND_XPOSED,
    // xposed hooks cleared.
    ANTIED_XPOSED,
    // can not clear hooks.
    CAN_NOT_ANTI_XPOSED,
};

int get_xposed_status(JNIEnv *env, int sdk);

#ifdef __cplusplus
}
#endif
