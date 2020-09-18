#pragma once

#include <jni.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

bool clearHooks(JNIEnv *env, jobject classLoader);

jclass findXposedBridge(JNIEnv *env, jobject classLoader);

bool disableXposedBridge(JNIEnv *env, jclass classXposedBridge);

#ifdef __cplusplus
}
#endif
