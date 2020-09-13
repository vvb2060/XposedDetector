#pragma once

#include <jni.h>

char *findObjectArrayName(JNIEnv *env, jobject clazz);

char *findStaticMapName(JNIEnv *env, jobject clazz);

char *findVoidStringName(JNIEnv *env, jobject clazz);
