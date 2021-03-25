#include <cstring>
#include "find-name.h"
#include "logging.h"
#include "obfs-string.h"

#define NATIVE 0x00000100
#define STATIC 0x00000008

static char *findField(C_JNIEnv *env, jobject clazz, int staticFlag, jclass type) {
    char *name = nullptr;
    jclass classClass = (*env)->FindClass((JNIEnv *) env, "java/lang/Class"_iobfs.c_str());
    jmethodID getDeclaredFields = (*env)->GetMethodID((JNIEnv *) env, classClass, "getDeclaredFields"_iobfs.c_str(), "()[Ljava/lang/reflect/Field;"_iobfs.c_str());
    jclass classField = (*env)->FindClass((JNIEnv *) env, "java/lang/reflect/Field"_iobfs.c_str());
    jmethodID getModifiers = (*env)->GetMethodID((JNIEnv *) env, classField, "getModifiers"_iobfs.c_str(), "()I"_iobfs.c_str());
    jmethodID getType = (*env)->GetMethodID((JNIEnv *) env, classField, "getType"_iobfs.c_str(), "()Ljava/lang/Class;"_iobfs.c_str());
    jmethodID getName = (*env)->GetMethodID((JNIEnv *) env, classField, "getName"_iobfs.c_str(), "()Ljava/lang/String;"_iobfs.c_str());
    auto fields = (jobjectArray) (*env)->CallObjectMethod((JNIEnv *) env, clazz, getDeclaredFields);
    int length = (*env)->GetArrayLength((JNIEnv *) env, fields);
    for (int i = 0; i < length; ++i) {
        jobject field = (*env)->GetObjectArrayElement((JNIEnv *) env, fields, i);
        debug(env, "field: %s", field);
        int modifier = (*env)->CallIntMethod((JNIEnv *) env, field, getModifiers);
        if ((modifier & STATIC) == staticFlag
            && (*env)->IsSameObject((JNIEnv *) env, type, (*env)->CallObjectMethod((JNIEnv *) env, field, getType))) {
            auto fieldString = (jstring) (*env)->CallObjectMethod((JNIEnv *) env, field, getName);
            const char *fieldName = (*env)->GetStringUTFChars((JNIEnv *) env, fieldString, nullptr);
            name = strdup(fieldName);
            (*env)->ReleaseStringUTFChars((JNIEnv *) env, fieldString, fieldName);
            (*env)->DeleteLocalRef((JNIEnv *) env, fieldString);
        }
        (*env)->DeleteLocalRef((JNIEnv *) env, field);
        if (name != nullptr) {
            break;
        }
    }

    (*env)->DeleteLocalRef((JNIEnv *) env, fields);
    (*env)->DeleteLocalRef((JNIEnv *) env, classField);
    (*env)->DeleteLocalRef((JNIEnv *) env, classClass);
    return name;
}

char *findObjectArrayName(C_JNIEnv *env, jobject clazz) {
    jclass classObjectArray = (*env)->FindClass((JNIEnv *) env, "[Ljava/lang/Object;"_iobfs.c_str());
    char *name = findField(env, clazz, 0, classObjectArray);
    (*env)->DeleteLocalRef((JNIEnv *) env, classObjectArray);
    return name;
}

char *findStaticMapName(C_JNIEnv *env, jobject clazz) {
    jclass classMap = (*env)->FindClass((JNIEnv *) env, "java/util/Map"_iobfs.c_str());
    char *name = findField(env, clazz, STATIC, classMap);
    (*env)->DeleteLocalRef((JNIEnv *) env, classMap);
    return name;
}

char *findVoidStringName(C_JNIEnv *env, jclass clazz) {
    char *name = nullptr;
    jclass classClass = (*env)->FindClass((JNIEnv *) env, "java/lang/Class"_iobfs.c_str());
    jmethodID getDeclaredMethods = (*env)->GetMethodID((JNIEnv *) env, classClass, "getDeclaredMethods"_iobfs.c_str(), "()[Ljava/lang/reflect/Method;"_iobfs.c_str());
    jclass classMethod = (*env)->FindClass((JNIEnv *) env, "java/lang/reflect/Method"_iobfs.c_str());
    jmethodID getModifiers = (*env)->GetMethodID((JNIEnv *) env, classMethod, "getModifiers"_iobfs.c_str(), "()I"_iobfs.c_str());
    jmethodID getParameterTypes = (*env)->GetMethodID((JNIEnv *) env, classMethod, "getParameterTypes"_iobfs.c_str(), "()[Ljava/lang/Class;"_iobfs.c_str());
    jmethodID getReturnType = (*env)->GetMethodID((JNIEnv *) env, classMethod, "getReturnType"_iobfs.c_str(), "()Ljava/lang/Class;"_iobfs.c_str());
    jmethodID getName = (*env)->GetMethodID((JNIEnv *) env, classMethod, "getName"_iobfs.c_str(), "()Ljava/lang/String;"_iobfs.c_str());
    jclass classString = (*env)->FindClass((JNIEnv *) env, "java/lang/String"_iobfs.c_str());
    auto methods = (jobjectArray) (*env)->CallObjectMethod((JNIEnv *) env, clazz, getDeclaredMethods);
    int length = (*env)->GetArrayLength((JNIEnv *) env, methods);
    for (int i = 0; i < length; ++i) {
        jobject method = (*env)->GetObjectArrayElement((JNIEnv *) env, methods, i);
        debug(env, "method: %s", method);
        int modifier = (*env)->CallIntMethod((JNIEnv *) env, method, getModifiers);
        if ((modifier & (NATIVE | STATIC)) == STATIC
            && (*env)->GetArrayLength((JNIEnv *) env, (jarray) (*env)->CallObjectMethod((JNIEnv *) env, method, getParameterTypes)) == 0
            && (*env)->IsSameObject((JNIEnv *) env, classString, (*env)->CallObjectMethod((JNIEnv *) env, method, getReturnType))) {
            auto methodString = (jstring) (*env)->CallObjectMethod((JNIEnv *) env, method, getName);
            const char *methodName = (*env)->GetStringUTFChars((JNIEnv *) env, methodString, nullptr);
            jmethodID methodMethod = (*env)->GetStaticMethodID((JNIEnv *) env, clazz, methodName, "()Ljava/lang/String;"_iobfs.c_str());
            auto bridgeString = (jstring) (*env)->CallStaticObjectMethod((JNIEnv *) env, clazz, methodMethod);
            if ((*env)->ExceptionCheck((JNIEnv *) env)) {
                (*env)->ExceptionClear((JNIEnv *) env);
            }
            if (bridgeString != nullptr) {
                const char *bridgeName = (*env)->GetStringUTFChars((JNIEnv *) env, bridgeString, nullptr);
#ifdef DEBUG
                LOGI("bridgeName: %s", bridgeName);
#endif
                if (*bridgeName == 'L') {
                    name = strdup(bridgeName + 1);
                } else {
                    name = strdup(bridgeName);
                }
                (*env)->ReleaseStringUTFChars((JNIEnv *) env, bridgeString, bridgeName);
                (*env)->DeleteLocalRef((JNIEnv *) env, bridgeString);
            }
            (*env)->ReleaseStringUTFChars((JNIEnv *) env, methodString, methodName);
            (*env)->DeleteLocalRef((JNIEnv *) env, methodString);
        }
        (*env)->DeleteLocalRef((JNIEnv *) env, method);
        if (name != nullptr) {
            char *x = name;
            while (*x != ';' && *x != '\0') {
                x++;
            }
            *x = '\0';
            break;
        }
    }

    (*env)->DeleteLocalRef((JNIEnv *) env, methods);
    (*env)->DeleteLocalRef((JNIEnv *) env, classString);
    (*env)->DeleteLocalRef((JNIEnv *) env, classMethod);
    (*env)->DeleteLocalRef((JNIEnv *) env, classClass);
    return name;
}
