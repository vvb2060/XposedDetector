#include "logging.h"

#ifdef DEBUG

void debug(C_JNIEnv *env, const char *format, jobject object) {
    if (object == nullptr) {
        LOGI(format, nullptr);
    } else {
        jclass objectClass = (*env)->FindClass((JNIEnv *) env, "java/lang/Object");
        jmethodID toString = (*env)->GetMethodID((JNIEnv *) env, objectClass, "toString", "()Ljava/lang/String;");
        auto string = (jstring) (*env)->CallObjectMethod((JNIEnv *) env, object, toString);
        const char *value = (*env)->GetStringUTFChars((JNIEnv *) env, string, nullptr);
        LOGI(format, value);
        (*env)->ReleaseStringUTFChars((JNIEnv *) env, string, value);
        (*env)->DeleteLocalRef((JNIEnv *) env, string);
        (*env)->DeleteLocalRef((JNIEnv *) env, objectClass);
    }
}

#endif
