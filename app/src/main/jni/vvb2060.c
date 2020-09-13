#include <stdio.h>
#include <string.h>
#include <jni.h>

#include "classloader.h"

jint JNI_OnLoad(JavaVM *jvm, void *v __unused) {
    JNIEnv *env;

    if ((*jvm)->GetEnv(jvm, (void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    checkClassLoader(env, android_get_device_api_level());

    return JNI_VERSION_1_6;
}
