#include <cstdlib>
#include "xposed.h"
#include "find-name.h"
#include "logging.h"
#include "obfs-string.h"
#include "hash.h"
#include "include/xposed-detector.h"

static jclass findLoadedClass(C_JNIEnv *env, jobject classLoader, const char *name) {
    jclass loadedClass = nullptr;
    jmethodID findLoadedClass;
    jstring string;

    debug(env, "findLoadedClass, classLoader: %s", classLoader);
#ifdef DEBUG
    LOGI("findLoadedClass, name: %s", name);
#endif

    jclass vmClassLoader = (*env)->FindClass((JNIEnv *) env, "java/lang/VMClassLoader"_iobfs.c_str());
    if ((*env)->ExceptionCheck((JNIEnv *) env)) {
        (*env)->ExceptionClear((JNIEnv *) env);
    }
    if (vmClassLoader == nullptr) {
        goto clean;
    }

    findLoadedClass = (*env)->GetStaticMethodID((JNIEnv *) env, vmClassLoader, "findLoadedClass"_iobfs.c_str(), "(Ljava/lang/ClassLoader;Ljava/lang/String;)Ljava/lang/Class;"_iobfs.c_str());
    if ((*env)->ExceptionCheck((JNIEnv *) env)) {
        (*env)->ExceptionClear((JNIEnv *) env);
    }
    if (findLoadedClass == nullptr) {
        goto cleanVmClassLoader;
    }

    string = (*env)->NewStringUTF((JNIEnv *) env, name);
    loadedClass = (jclass) (*env)->CallStaticObjectMethod((JNIEnv *) env, vmClassLoader, findLoadedClass, classLoader, string);

    if ((*env)->ExceptionCheck((JNIEnv *) env)) {
        (*env)->ExceptionClear((JNIEnv *) env);
    }

#ifdef DEBUG
    debug(env, "loaded class: %s", loadedClass);
#endif

    (*env)->DeleteLocalRef((JNIEnv *) env, string);
    cleanVmClassLoader:
    (*env)->DeleteLocalRef((JNIEnv *) env, vmClassLoader);
    clean:
    return loadedClass;
}

static jclass findXposedBridge(C_JNIEnv *env, jobject classLoader) {
    return findLoadedClass(env, classLoader, "de/robv/android/xposed/XposedBridge"_iobfs.c_str());
}

static bool disableXposedBridge(C_JNIEnv *env, jclass classXposedBridge) {
    jfieldID field = (*env)->GetStaticFieldID((JNIEnv *) env, classXposedBridge, "disableHooks"_iobfs.c_str(), "Z"_iobfs.c_str());
    if ((*env)->ExceptionCheck((JNIEnv *) env)) {
        (*env)->ExceptionClear((JNIEnv *) env);
    }
    if (field == nullptr) {
        return false;
    }
    (*env)->SetStaticBooleanField((JNIEnv *) env, classXposedBridge, field, JNI_TRUE);
    if ((*env)->ExceptionCheck((JNIEnv *) env)) {
        (*env)->ExceptionClear((JNIEnv *) env);
        return false;
    }
    return true;
}

static jfieldID findMapField(C_JNIEnv *env, jclass classXposedBridge) {
    auto signature = "Ljava/util/Map;"_iobfs;
    jfieldID field = (*env)->GetStaticFieldID((JNIEnv *) env, classXposedBridge, "sHookedMethodCallbacks"_iobfs.c_str(), signature.c_str());
    if ((*env)->ExceptionCheck((JNIEnv *) env)) {
        (*env)->ExceptionClear((JNIEnv *) env);
    }
    if (field != nullptr) {
        return field;
    }
    debug(env, "cannot find sHookedMethodCallbacks in %s", classXposedBridge);
    const char *mapName = findStaticMapName(env, classXposedBridge);
    if (mapName != nullptr) {
#ifdef DEBUG
        LOGI("mapName: %s", mapName);
#endif
        return (*env)->GetStaticFieldID((JNIEnv *) env, classXposedBridge, mapName, signature.c_str());
    }
    debug(env, "cannot find static map in %s", classXposedBridge);
    return nullptr;
}

static bool doClearHooksClass(C_JNIEnv *env, jclass classXposedBridge) {
    bool antied = false;

    jfieldID field = findMapField(env, classXposedBridge);
    if (field == nullptr) {
        return false;
    }
    jobject map = (*env)->GetStaticObjectField((JNIEnv *) env, classXposedBridge, field);
    debug(env, "hooks: %s", map);

    jclass classMap = (*env)->FindClass((JNIEnv *) env, "java/util/HashMap"_iobfs.c_str());
    if (map == nullptr || !(*env)->IsInstanceOf((JNIEnv *) env, map, classMap)) {
        return false;
    }

    jmethodID method = (*env)->GetMethodID((JNIEnv *) env, classMap, "isEmpty"_iobfs.c_str(), "()Z"_iobfs.c_str());
    jboolean isEmpty = (*env)->CallBooleanMethod((JNIEnv *) env, map, method);
    if (isEmpty == JNI_TRUE) {
        isEmpty = (*env)->CallNonvirtualBooleanMethod((JNIEnv *) env, map, (*env)->GetObjectClass((JNIEnv *) env, map), method);
    }

    jobject values;
    method = (*env)->GetMethodID((JNIEnv *) env, classMap, "values"_iobfs.c_str(), "()Ljava/util/Collection;"_iobfs.c_str());
    if (isEmpty == JNI_TRUE) {
        values = (*env)->CallObjectMethod((JNIEnv *) env, map, method);
    } else {
        values = (*env)->CallNonvirtualObjectMethod((JNIEnv *) env, map, (*env)->GetObjectClass((JNIEnv *) env, map), method);
    }

    jclass classCollection = (*env)->FindClass((JNIEnv *) env, "java/util/Collection"_iobfs.c_str());
    method = (*env)->GetMethodID((JNIEnv *) env, classCollection, "iterator"_iobfs.c_str(), "()Ljava/util/Iterator;"_iobfs.c_str());
    jobject iterator = (*env)->CallObjectMethod((JNIEnv *) env, values, method);

    jclass classIterator = (*env)->FindClass((JNIEnv *) env, "java/util/Iterator"_iobfs.c_str());
    jmethodID hasNext = (*env)->GetMethodID((JNIEnv *) env, classIterator, "hasNext"_iobfs.c_str(), "()Z"_iobfs.c_str());
    jmethodID next = (*env)->GetMethodID((JNIEnv *) env, classIterator, "next"_iobfs.c_str(), "()Ljava/lang/Object;"_iobfs.c_str());

    jclass classObject = (*env)->FindClass((JNIEnv *) env, "java/lang/Object"_iobfs.c_str());
    jobject emptyArray = (*env)->NewObjectArray((JNIEnv *) env, 0, classObject, nullptr);
    jfieldID fieldElements = nullptr;
    while ((*env)->CallBooleanMethod((JNIEnv *) env, iterator, hasNext)) {
        jobject hook = (*env)->CallObjectMethod((JNIEnv *) env, iterator, next);
        debug(env, "hook value: %s", hook);
        if (hook == nullptr) {
            continue;
        }
        if (fieldElements == nullptr) {
            jclass hookClass = (*env)->GetObjectClass((JNIEnv *) env, hook);
            char *name = findObjectArrayName(env, hookClass);
            if (name == nullptr) {
                (*env)->DeleteLocalRef((JNIEnv *) env, hookClass);
                break;
            }
            fieldElements = (*env)->GetFieldID((JNIEnv *) env, hookClass, name, "[Ljava/lang/Object;"_iobfs.c_str());
            free(name);
            (*env)->DeleteLocalRef((JNIEnv *) env, hookClass);
        }
        (*env)->SetObjectField((JNIEnv *) env, hook, fieldElements, emptyArray);
        if ((*env)->ExceptionCheck((JNIEnv *) env)) {
            (*env)->ExceptionClear((JNIEnv *) env);
        } else if (!antied) {
            antied = true;
        }
        (*env)->DeleteLocalRef((JNIEnv *) env, hook);
    }

    (*env)->DeleteLocalRef((JNIEnv *) env, classIterator);
    (*env)->DeleteLocalRef((JNIEnv *) env, iterator);
    (*env)->DeleteLocalRef((JNIEnv *) env, classCollection);
    (*env)->DeleteLocalRef((JNIEnv *) env, values);
    (*env)->DeleteLocalRef((JNIEnv *) env, classMap);
    (*env)->DeleteLocalRef((JNIEnv *) env, map);

    return antied;
}

static bool doClearHooksCommon(C_JNIEnv *env, jobject classLoader, const char *name) {
    bool antied = false;
    jclass classXposedBridge = findLoadedClass(env, classLoader, name);
    if (classXposedBridge != nullptr) {
#ifdef DEBUG
        LOGI("found %s", name);
#endif
        antied = doClearHooksClass(env, (jclass) classXposedBridge);
        (*env)->DeleteLocalRef((JNIEnv *) env, classXposedBridge);
    }
    return antied;
}

static bool clearHooks(C_JNIEnv *env, jobject classLoader) {
    bool antied = false;

    debug(env, "clearHooks, classLoader: %s", classLoader);

    jclass epicNative = findLoadedClass(env, classLoader, "me/weishu/epic/art2/EpicNative"_iobfs.c_str());
    if (epicNative != nullptr) {
        char *bridgeClass = findVoidStringName(env, epicNative);
#ifdef DEBUG
        LOGI("bridge class: %s", bridgeClass);
#endif
        if (bridgeClass != nullptr) {
            antied |= doClearHooksCommon(env, classLoader, bridgeClass);
            free(bridgeClass);
        }
        (*env)->DeleteLocalRef((JNIEnv *) env, epicNative);
    }
    if (!antied) {
        antied |= doClearHooksCommon(env, classLoader, "me/weishu/epic/art2/EpicBridge"_iobfs.c_str());
    }
    if (!antied) {
        antied |= doClearHooksCommon(env, classLoader, "de/robv/android/xposed/DexposedBridge"_iobfs.c_str());
    }
    if (!antied) {
        antied |= doClearHooksCommon(env, classLoader, "de/robv/android/xposed/XposedBridge"_iobfs.c_str());
    }

    return antied;
}

void doAntiXposed(C_JNIEnv *env, jobject object, intptr_t hash) {
    if (!add(hash)) {
        debug(env, "checked classLoader %s", object);
        return;
    }
#ifdef DEBUG
    LOGI("doAntiXposed, classLoader: %p, hash: %zx", object, hash);
#endif
    jclass classXposedBridge = findXposedBridge(env, object);
    if (classXposedBridge == nullptr) {
        return;
    }
    if (xposed_status == NO_XPOSED) {
        xposed_status = FOUND_XPOSED;
    }
    disableXposedBridge(env, classXposedBridge);
    if (clearHooks(env, object)) {
#ifdef DEBUG
        LOGI("hooks cleared");
#endif
        if (xposed_status < ANTIED_XPOSED) {
            xposed_status = ANTIED_XPOSED;
        }
    }
}

void checkCallStack(C_JNIEnv *env) {
    jclass threadClass = (*env)->FindClass((JNIEnv *) env, "java/lang/Thread"_iobfs.c_str());
    jmethodID currentThread = (*env)->GetStaticMethodID((JNIEnv *) env, threadClass, "currentThread"_iobfs.c_str(), "()Ljava/lang/Thread;"_iobfs.c_str());
    jmethodID getStackTrace = (*env)->GetMethodID((JNIEnv *) env, threadClass, "getStackTrace"_iobfs.c_str(), "()[Ljava/lang/StackTraceElement;"_iobfs.c_str());
    jclass StackTraceElementClass = (*env)->FindClass((JNIEnv *) env, "java/lang/StackTraceElement"_iobfs.c_str());
    jmethodID getClassName = (*env)->GetMethodID((JNIEnv *) env, StackTraceElementClass, "getClassName"_iobfs.c_str(), "()Ljava/lang/String;"_iobfs.c_str());

    jobject thread = (*env)->CallStaticObjectMethod((JNIEnv *) env, threadClass, currentThread);
    auto stackTraces = (jobjectArray) (*env)->CallObjectMethod((JNIEnv *) env, thread, getStackTrace);
    int length = (*env)->GetArrayLength((JNIEnv *) env, stackTraces);
    for (int i = 0; i < length; i++) {
        jobject stackTrace = (*env)->GetObjectArrayElement((JNIEnv *) env, stackTraces, i);
        debug(env, "stackTrace: %s", stackTrace);
        auto jclassName = (jstring) (*env)->CallObjectMethod((JNIEnv *) env, stackTrace, getClassName);
        const char *className = (*env)->GetStringUTFChars((JNIEnv *) env, jclassName, nullptr);
        auto methodHook = "de.robv.android.xposed.XC_MethodHook"_iobfs;
        if (memcmp(className, methodHook.c_str(), methodHook.size()) == 0) {
            LOGD("Call stack found hook: %s", className);
            xposed_status = CAN_NOT_ANTI_XPOSED;
        }
        (*env)->ReleaseStringUTFChars((JNIEnv *) env, jclassName, className);
        if (xposed_status == CAN_NOT_ANTI_XPOSED) break;
    }
}
