#include <jni.h>
#include "xposed-detector.h"

static int xposed_stat = NO_XPOSED;

jint getXposedStat(JNIEnv *, jobject) {
    return xposed_stat;
}

jint JNI_OnLoad(JavaVM *jvm, void *) {
    JNIEnv *env;
    jclass clazz;

    if (jvm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    xposed_stat = get_xposed_status(env, android_get_device_api_level());

    if ((clazz = env->FindClass("io/github/vvb2060/xposeddetector/MainActivity")) == nullptr) {
        return JNI_ERR;
    }

    JNINativeMethod methods[] = {
            {"getXposedStat", "()I", reinterpret_cast<void *>(getXposedStat)}
    };

    if (env->RegisterNatives(clazz, methods, 1) < 0) {
        return JNI_ERR;
    }

    return JNI_VERSION_1_6;
}
