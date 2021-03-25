#pragma once

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

char *findObjectArrayName(C_JNIEnv *env, jobject clazz);

char *findStaticMapName(C_JNIEnv *env, jobject clazz);

char *findVoidStringName(C_JNIEnv *env, jclass clazz);

#ifdef __cplusplus
}
#endif
