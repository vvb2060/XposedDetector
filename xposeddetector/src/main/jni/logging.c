#include "logging.h"

#ifdef DEBUG

void debug(JNIEnv *env, const char *format, jobject object) {
    if (object == NULL) {
        LOGI(format, NULL);
    } else {
        jclass objectClass = (*env)->FindClass(env, "java/lang/Object");
        jmethodID toString = (*env)->GetMethodID(env, objectClass, "toString",
                                                 "()Ljava/lang/String;");
        jstring string = (jstring) (*env)->CallObjectMethod(env, object, toString);
        const char *value = (*env)->GetStringUTFChars(env, string, NULL);
        LOGI(format, value);
        (*env)->ReleaseStringUTFChars(env, string, value);
        (*env)->DeleteLocalRef(env, string);
        (*env)->DeleteLocalRef(env, objectClass);
    }
}

#endif
