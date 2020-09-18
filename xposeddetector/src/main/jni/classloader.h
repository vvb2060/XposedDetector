#pragma once

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int xposed_status;

void checkClassLoader(JNIEnv *env, int sdk);

#ifdef __cplusplus
}
#endif
