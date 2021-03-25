#pragma once

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

void checkClassLoader(C_JNIEnv *env, int sdk);

#ifdef __cplusplus
}
#endif
