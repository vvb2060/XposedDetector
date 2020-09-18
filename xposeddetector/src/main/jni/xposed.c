#include <stdlib.h>
#include "xposed.h"
#include "find-name.h"
#include "logging.h"

static inline void fill_java_lang_VMClassLoader(char v[]) {
    // java/lang/VMClassLoader
    static unsigned int m = 0;

    if (m == 0) {
        m = 19;
    } else if (m == 23) {
        m = 29;
    }

    v[0x0] = 'n';
    v[0x1] = 'd';
    v[0x2] = 'p';
    v[0x3] = 'f';
    v[0x4] = '\'';
    v[0x5] = 'e';
    v[0x6] = 'k';
    v[0x7] = 'e';
    v[0x8] = 'k';
    v[0x9] = '"';
    v[0xa] = 'X';
    v[0xb] = 'B';
    v[0xc] = 'S';
    v[0xd] = '}';
    v[0xe] = 's';
    v[0xf] = 's';
    v[0x10] = 'r';
    v[0x11] = 'N';
    v[0x12] = 'l';
    v[0x13] = 'e';
    v[0x14] = 'a';
    v[0x15] = 'c';
    v[0x16] = 'u';
    for (unsigned int i = 0; i < 0x17; ++i) {
        v[i] ^= ((i + 0x17) % m);
    }
    v[0x17] = '\0';
}

static inline void fill_findLoadedClass(char v[]) {
    // findLoadedClass
    static unsigned int m = 0;

    if (m == 0) {
        m = 13;
    } else if (m == 17) {
        m = 19;
    }

    v[0x0] = 'd';
    v[0x1] = 'j';
    v[0x2] = 'j';
    v[0x3] = 'a';
    v[0x4] = 'J';
    v[0x5] = 'h';
    v[0x6] = 'i';
    v[0x7] = 'm';
    v[0x8] = 'o';
    v[0x9] = 'o';
    v[0xa] = 'O';
    v[0xb] = 'l';
    v[0xc] = '`';
    v[0xd] = 'q';
    v[0xe] = 'p';
    for (unsigned int i = 0; i < 0xf; ++i) {
        v[i] ^= ((i + 0xf) % m);
    }
    v[0xf] = '\0';
}

static inline void fill_findLoadedClass_signature(char v[]) {
    // (Ljava/lang/ClassLoader;Ljava/lang/String;)Ljava/lang/Class;
    static unsigned int m = 0;

    if (m == 0) {
        m = 59;
    } else if (m == 61) {
        m = 67;
    }

    v[0x0] = ')';
    v[0x1] = 'N';
    v[0x2] = 'i';
    v[0x3] = 'e';
    v[0x4] = 's';
    v[0x5] = 'g';
    v[0x6] = '(';
    v[0x7] = 'd';
    v[0x8] = 'h';
    v[0x9] = 'd';
    v[0xa] = 'l';
    v[0xb] = '#';
    v[0xc] = 'N';
    v[0xd] = 'b';
    v[0xe] = 'n';
    v[0xf] = 'c';
    v[0x10] = 'b';
    v[0x11] = '^';
    v[0x12] = '|';
    v[0x13] = 'u';
    v[0x14] = 'q';
    v[0x15] = 's';
    v[0x16] = 'e';
    v[0x17] = '#';
    v[0x18] = 'U';
    v[0x19] = 'p';
    v[0x1a] = 'z';
    v[0x1b] = 'j';
    v[0x1c] = '|';
    v[0x1d] = '1';
    v[0x1e] = 's';
    v[0x1f] = 'A';
    v[0x20] = 'O';
    v[0x21] = 'E';
    v[0x22] = '\x0c';
    v[0x23] = 'w';
    v[0x24] = 'Q';
    v[0x25] = 'T';
    v[0x26] = 'N';
    v[0x27] = 'F';
    v[0x28] = 'N';
    v[0x29] = '\x11';
    v[0x2a] = '\x02';
    v[0x2b] = '`';
    v[0x2c] = 'G';
    v[0x2d] = 'O';
    v[0x2e] = 'Y';
    v[0x2f] = 'Q';
    v[0x30] = '\x1e';
    v[0x31] = '^';
    v[0x32] = 'R';
    v[0x33] = 'Z';
    v[0x34] = 'R';
    v[0x35] = '\x19';
    v[0x36] = 't';
    v[0x37] = 'T';
    v[0x38] = 'X';
    v[0x39] = 'I';
    v[0x3a] = 's';
    v[0x3b] = ':';
    for (unsigned int i = 0; i < 0x3c; ++i) {
        v[i] ^= ((i + 0x3c) % m);
    }
    v[0x3c] = '\0';
}

static inline void fill_de_robv_android_xposed_XposedBridge(char v[]) {
    // de/robv/android/xposed/XposedBridge
    static unsigned int m = 0;

    if (m == 0) {
        m = 31;
    } else if (m == 37) {
        m = 41;
    }

    v[0x0] = '`';
    v[0x1] = '`';
    v[0x2] = ')';
    v[0x3] = 'u';
    v[0x4] = 'g';
    v[0x5] = 'k';
    v[0x6] = '|';
    v[0x7] = '$';
    v[0x8] = 'm';
    v[0x9] = 'c';
    v[0xa] = 'j';
    v[0xb] = '}';
    v[0xc] = '\x7f';
    v[0xd] = 'x';
    v[0xe] = 'v';
    v[0xf] = '<';
    v[0x10] = 'l';
    v[0x11] = 'e';
    v[0x12] = 'y';
    v[0x13] = 'd';
    v[0x14] = '}';
    v[0x15] = '}';
    v[0x16] = '5';
    v[0x17] = 'C';
    v[0x18] = 'l';
    v[0x19] = 'r';
    v[0x1a] = 'm';
    v[0x1b] = 'e';
    v[0x1c] = 'e';
    v[0x1d] = '@';
    v[0x1e] = 'q';
    v[0x1f] = 'm';
    v[0x20] = 'a';
    v[0x21] = 'a';
    v[0x22] = 'b';
    for (unsigned int i = 0; i < 0x23; ++i) {
        v[i] ^= ((i + 0x23) % m);
    }
    v[0x23] = '\0';
}

static inline void fill_disableHooks(char v[]) {
    // disableHooks
    static unsigned int m = 0;

    if (m == 0) {
        m = 11;
    } else if (m == 13) {
        m = 17;
    }

    v[0x0] = 'e';
    v[0x1] = 'k';
    v[0x2] = 'p';
    v[0x3] = 'e';
    v[0x4] = 'g';
    v[0x5] = 'j';
    v[0x6] = 'b';
    v[0x7] = '@';
    v[0x8] = 'f';
    v[0x9] = 'e';
    v[0xa] = 'k';
    v[0xb] = 'r';
    for (unsigned int i = 0; i < 0xc; ++i) {
        v[i] ^= ((i + 0xc) % m);
    }
    v[0xc] = '\0';

}

static inline void fill_disableHooks_signature(char v[]) {
    // Z
    static unsigned int m = 0;

    if (m == 0) {
        m = 2;
    } else if (m == 3) {
        m = 5;
    }

    v[0x0] = '[';
    for (unsigned int i = 0; i < 0x1; ++i) {
        v[i] ^= ((i + 0x1) % m);
    }
    v[0x1] = '\0';
}

jclass findLoadedClass(JNIEnv *env, jobject classLoader, const char *name) {
    char v1[0x80], v2[0x80];
    jclass loadedClass = NULL;

    debug(env, "findLoadedClass, classLoader: %s", classLoader);
#ifdef DEBUG
    LOGI("findLoadedClass, name: %s", name);
#endif

    fill_java_lang_VMClassLoader(v1);
    jclass vmClassLoader = (*env)->FindClass(env, v1);
    if ((*env)->ExceptionCheck(env)) {
        (*env)->ExceptionClear(env);
    }
    if (vmClassLoader == NULL) {
        goto clean;
    }

    fill_findLoadedClass(v1);
    fill_findLoadedClass_signature(v2);
    jmethodID findLoadedClass = (*env)->GetStaticMethodID(env, vmClassLoader, v1, v2);
    if ((*env)->ExceptionCheck(env)) {
        (*env)->ExceptionClear(env);
    }
    if (findLoadedClass == NULL) {
        goto cleanVmClassLoader;
    }

    jstring string = (*env)->NewStringUTF(env, name);
    loadedClass = (jclass) (*env)->CallStaticObjectMethod(env,
                                                          vmClassLoader,
                                                          findLoadedClass,
                                                          classLoader,
                                                          string);

    if ((*env)->ExceptionCheck(env)) {
        (*env)->ExceptionClear(env);
    }

#ifdef DEBUG
    debug(env, "loaded class: %s", loadedClass);
#endif

    (*env)->DeleteLocalRef(env, string);
    cleanVmClassLoader:
    (*env)->DeleteLocalRef(env, vmClassLoader);
    clean:
    return loadedClass;
}

jclass findXposedBridge(JNIEnv *env, jobject classLoader) {
    char v1[0x80];
    fill_de_robv_android_xposed_XposedBridge(v1);
    return findLoadedClass(env, classLoader, v1);
}

bool disableXposedBridge(JNIEnv *env, jclass classXposedBridge) {
    char v1[0x80], v2[0x80];
    fill_disableHooks(v1);
    fill_disableHooks_signature(v2);
    jfieldID field = (*env)->GetStaticFieldID(env, classXposedBridge, v1, v2);
    if ((*env)->ExceptionCheck(env)) {
        (*env)->ExceptionClear(env);
    }
    if (field == NULL) {
        return false;
    }
    (*env)->SetStaticBooleanField(env, classXposedBridge, field, JNI_TRUE);
    if ((*env)->ExceptionCheck(env)) {
        (*env)->ExceptionClear(env);
        return false;
    }
    return true;
}

static inline void fill_me_weishu_epic_art2_EpicNative(char v[]) {
    // me/weishu/epic/art2/EpicNative
    static unsigned int m = 0;

    if (m == 0) {
        m = 29;
    } else if (m == 31) {
        m = 37;
    }

    v[0x0] = 'l';
    v[0x1] = 'g';
    v[0x2] = ',';
    v[0x3] = 's';
    v[0x4] = '`';
    v[0x5] = 'o';
    v[0x6] = 't';
    v[0x7] = '`';
    v[0x8] = '|';
    v[0x9] = '%';
    v[0xa] = 'n';
    v[0xb] = '|';
    v[0xc] = 'd';
    v[0xd] = 'm';
    v[0xe] = ' ';
    v[0xf] = 'q';
    v[0x10] = 'c';
    v[0x11] = 'f';
    v[0x12] = '!';
    v[0x13] = ';';
    v[0x14] = 'P';
    v[0x15] = 'f';
    v[0x16] = '~';
    v[0x17] = '{';
    v[0x18] = 'W';
    v[0x19] = '{';
    v[0x1a] = 'o';
    v[0x1b] = 'u';
    v[0x1c] = 'v';
    v[0x1d] = 'd';
    for (unsigned int i = 0; i < 0x1e; ++i) {
        v[i] ^= ((i + 0x1e) % m);
    }
    v[0x1e] = '\0';
}

static inline void fill_me_weishu_epic_art2_EpicBridge(char v[]) {
    // me/weishu/epic/art2/EpicBridge
    static unsigned int m = 0;

    if (m == 0) {
        m = 29;
    } else if (m == 31) {
        m = 37;
    }

    v[0x0] = 'l';
    v[0x1] = 'g';
    v[0x2] = ',';
    v[0x3] = 's';
    v[0x4] = '`';
    v[0x5] = 'o';
    v[0x6] = 't';
    v[0x7] = '`';
    v[0x8] = '|';
    v[0x9] = '%';
    v[0xa] = 'n';
    v[0xb] = '|';
    v[0xc] = 'd';
    v[0xd] = 'm';
    v[0xe] = ' ';
    v[0xf] = 'q';
    v[0x10] = 'c';
    v[0x11] = 'f';
    v[0x12] = '!';
    v[0x13] = ';';
    v[0x14] = 'P';
    v[0x15] = 'f';
    v[0x16] = '~';
    v[0x17] = '{';
    v[0x18] = '[';
    v[0x19] = 'h';
    v[0x1a] = 'r';
    v[0x1b] = 'x';
    v[0x1c] = 'g';
    v[0x1d] = 'd';
    for (unsigned int i = 0; i < 0x1e; ++i) {
        v[i] ^= ((i + 0x1e) % m);
    }
    v[0x1e] = '\0';
}

static inline void fill_sHookedMethodCallbacks(char v[]) {
    // sHookedMethodCallbacks
    static unsigned int m = 0;

    if (m == 0) {
        m = 19;
    } else if (m == 23) {
        m = 29;
    }

    v[0x0] = 'p';
    v[0x1] = 'L';
    v[0x2] = 'j';
    v[0x3] = 'i';
    v[0x4] = 'l';
    v[0x5] = 'm';
    v[0x6] = 'm';
    v[0x7] = 'G';
    v[0x8] = 'n';
    v[0x9] = 'x';
    v[0xa] = 'e';
    v[0xb] = 'a';
    v[0xc] = 'k';
    v[0xd] = 'S';
    v[0xe] = 'p';
    v[0xf] = '~';
    v[0x10] = 'l';
    v[0x11] = 'c';
    v[0x12] = 'c';
    v[0x13] = '`';
    v[0x14] = 'o';
    v[0x15] = 'v';
    for (unsigned int i = 0; i < 0x16; ++i) {
        v[i] ^= ((i + 0x16) % m);
    }
    v[0x16] = '\0';
}

static inline void fill_sHookedMethodCallbacks_signature(char *v) {
    // Ljava/util/Map;
    static unsigned int m = 0;

    if (m == 0) {
        m = 13;
    } else if (m == 17) {
        m = 19;
    }

    v[0x0] = 'N';
    v[0x1] = 'i';
    v[0x2] = 'e';
    v[0x3] = 's';
    v[0x4] = 'g';
    v[0x5] = '(';
    v[0x6] = '}';
    v[0x7] = '}';
    v[0x8] = 'c';
    v[0x9] = 'g';
    v[0xa] = '#';
    v[0xb] = 'M';
    v[0xc] = '`';
    v[0xd] = 'r';
    v[0xe] = '8';
    for (unsigned int i = 0; i < 0xf; ++i) {
        v[i] ^= ((i + 0xf) % m);
    }
    v[0xf] = '\0';
}

static inline void fill_java_util_Map(char v[]) {
    // java/util/Map
    static unsigned int m = 0;

    if (m == 0) {
        m = 11;
    } else if (m == 13) {
        m = 17;
    }

    v[0x0] = 'h';
    v[0x1] = 'b';
    v[0x2] = 'r';
    v[0x3] = 'd';
    v[0x4] = ')';
    v[0x5] = 'r';
    v[0x6] = '|';
    v[0x7] = '`';
    v[0x8] = 'f';
    v[0x9] = '/';
    v[0xa] = 'L';
    v[0xb] = 'c';
    v[0xc] = 's';
    for (unsigned int i = 0; i < 0xd; ++i) {
        v[i] ^= ((i + 0xd) % m);
    }
    v[0xd] = '\0';
}

static inline void fill_values(char v[]) {
    // values
    static unsigned int m = 0;

    if (m == 0) {
        m = 5;
    } else if (m == 7) {
        m = 11;
    }

    v[0x0] = 'w';
    v[0x1] = 'c';
    v[0x2] = 'o';
    v[0x3] = 'q';
    v[0x4] = 'e';
    v[0x5] = 'r';
    for (unsigned int i = 0; i < 0x6; ++i) {
        v[i] ^= ((i + 0x6) % m);
    }
    v[0x6] = '\0';
}

static inline void fill_values_signature(char v[]) {
    // ()Ljava/util/Collection;
    static unsigned int m = 0;

    if (m == 0) {
        m = 23;
    } else if (m == 29) {
        m = 31;
    }

    v[0x0] = ')';
    v[0x1] = '+';
    v[0x2] = 'O';
    v[0x3] = 'n';
    v[0x4] = 'd';
    v[0x5] = 'p';
    v[0x6] = 'f';
    v[0x7] = '\'';
    v[0x8] = '|';
    v[0x9] = '~';
    v[0xa] = 'b';
    v[0xb] = '`';
    v[0xc] = '"';
    v[0xd] = 'M';
    v[0xe] = '`';
    v[0xf] = '|';
    v[0x10] = '}';
    v[0x11] = 'w';
    v[0x12] = 'p';
    v[0x13] = '`';
    v[0x14] = '|';
    v[0x15] = 'y';
    v[0x16] = 'n';
    v[0x17] = ':';
    for (unsigned int i = 0; i < 0x18; ++i) {
        v[i] ^= ((i + 0x18) % m);
    }
    v[0x18] = '\0';
}

static inline void fill_java_util_Collection(char v[]) {
    // java/util/Collection
    static unsigned int m = 0;

    if (m == 0) {
        m = 19;
    } else if (m == 23) {
        m = 29;
    }

    v[0x0] = 'k';
    v[0x1] = 'c';
    v[0x2] = 'u';
    v[0x3] = 'e';
    v[0x4] = '*';
    v[0x5] = 's';
    v[0x6] = 's';
    v[0x7] = 'a';
    v[0x8] = 'e';
    v[0x9] = '%';
    v[0xa] = 'H';
    v[0xb] = 'c';
    v[0xc] = 'a';
    v[0xd] = 'b';
    v[0xe] = 'j';
    v[0xf] = 's';
    v[0x10] = 'e';
    v[0x11] = '{';
    v[0x12] = 'o';
    v[0x13] = 'o';
    for (unsigned int i = 0; i < 0x14; ++i) {
        v[i] ^= ((i + 0x14) % m);
    }
    v[0x14] = '\0';
}

static inline void fill_iterator(char v[]) {
    // iterator
    static unsigned int m = 0;

    if (m == 0) {
        m = 7;
    } else if (m == 11) {
        m = 13;
    }

    v[0x0] = 'h';
    v[0x1] = 'v';
    v[0x2] = 'f';
    v[0x3] = 'v';
    v[0x4] = 'd';
    v[0x5] = 'r';
    v[0x6] = 'o';
    v[0x7] = 's';
    for (unsigned int i = 0; i < 0x8; ++i) {
        v[i] ^= ((i + 0x8) % m);
    }
    v[0x8] = '\0';
}

static inline void fill_iterator_signature(char v[]) {
    // ()Ljava/util/Iterator;
    static unsigned int m = 0;

    if (m == 0) {
        m = 19;
    } else if (m == 23) {
        m = 29;
    }

    v[0x0] = '+';
    v[0x1] = '-';
    v[0x2] = 'I';
    v[0x3] = 'l';
    v[0x4] = 'f';
    v[0x5] = '~';
    v[0x6] = 'h';
    v[0x7] = '%';
    v[0x8] = '~';
    v[0x9] = 'x';
    v[0xa] = 'd';
    v[0xb] = 'b';
    v[0xc] = ' ';
    v[0xd] = 'Y';
    v[0xe] = 'e';
    v[0xf] = 'w';
    v[0x10] = 'r';
    v[0x11] = '`';
    v[0x12] = 'v';
    v[0x13] = 'l';
    v[0x14] = 'v';
    v[0x15] = '>';
    for (unsigned int i = 0; i < 0x16; ++i) {
        v[i] ^= ((i + 0x16) % m);
    }
    v[0x16] = '\0';
}

static inline void fill_java_util_Iterator(char v[]) {
    // java/util/Iterator
    static unsigned int m = 0;

    if (m == 0) {
        m = 17;
    } else if (m == 19) {
        m = 23;
    }

    v[0x0] = 'k';
    v[0x1] = 'c';
    v[0x2] = 'u';
    v[0x3] = 'e';
    v[0x4] = '*';
    v[0x5] = 's';
    v[0x6] = 's';
    v[0x7] = 'a';
    v[0x8] = 'e';
    v[0x9] = '%';
    v[0xa] = 'B';
    v[0xb] = 'x';
    v[0xc] = 'h';
    v[0xd] = '|';
    v[0xe] = 'n';
    v[0xf] = 'd';
    v[0x10] = 'o';
    v[0x11] = 's';
    for (unsigned int i = 0; i < 0x12; ++i) {
        v[i] ^= ((i + 0x12) % m);
    }
    v[0x12] = '\0';
}

static inline void fill_hasNext(char v[]) {
    // hasNext
    static unsigned int m = 0;

    if (m == 0) {
        m = 5;
    } else if (m == 7) {
        m = 11;
    }

    v[0x0] = 'j';
    v[0x1] = 'b';
    v[0x2] = 'w';
    v[0x3] = 'N';
    v[0x4] = 'd';
    v[0x5] = 'z';
    v[0x6] = 'w';
    for (unsigned int i = 0; i < 0x7; ++i) {
        v[i] ^= ((i + 0x7) % m);
    }
    v[0x7] = '\0';
}

static inline void fill_hasNext_signature(char v[]) {
    // ()Z
    static unsigned int m = 0;

    if (m == 0) {
        m = 2;
    } else if (m == 3) {
        m = 5;
    }

    v[0x0] = ')';
    v[0x1] = ')';
    v[0x2] = '[';
    for (unsigned int i = 0; i < 0x3; ++i) {
        v[i] ^= ((i + 0x3) % m);
    }
    v[0x3] = '\0';
}

static inline void fill_next(char v[]) {
    // next
    static unsigned int m = 0;

    if (m == 0) {
        m = 3;
    } else if (m == 5) {
        m = 7;
    }

    v[0x0] = 'o';
    v[0x1] = 'g';
    v[0x2] = 'x';
    v[0x3] = 'u';
    for (unsigned int i = 0; i < 0x4; ++i) {
        v[i] ^= ((i + 0x4) % m);
    }
    v[0x4] = '\0';
}

static inline void fill_next_signature(char v[]) {
    // ()Ljava/lang/Object;
    static unsigned int m = 0;

    if (m == 0) {
        m = 19;
    } else if (m == 23) {
        m = 29;
    }

    v[0x0] = ')';
    v[0x1] = '+';
    v[0x2] = 'O';
    v[0x3] = 'n';
    v[0x4] = 'd';
    v[0x5] = 'p';
    v[0x6] = 'f';
    v[0x7] = '\'';
    v[0x8] = 'e';
    v[0x9] = 'k';
    v[0xa] = 'e';
    v[0xb] = 'k';
    v[0xc] = '"';
    v[0xd] = 'A';
    v[0xe] = 'm';
    v[0xf] = 'z';
    v[0x10] = 't';
    v[0x11] = 'q';
    v[0x12] = 't';
    v[0x13] = ':';
    for (unsigned int i = 0; i < 0x14; ++i) {
        v[i] ^= ((i + 0x14) % m);
    }
    v[0x14] = '\0';
}

static inline void fill_signature(char v[]) {
    // [Ljava/lang/Object;
    static unsigned int m = 0;

    if (m == 0) {
        m = 17;
    } else if (m == 19) {
        m = 23;
    }

    v[0x0] = 'Y';
    v[0x1] = 'O';
    v[0x2] = 'n';
    v[0x3] = 'd';
    v[0x4] = 'p';
    v[0x5] = 'f';
    v[0x6] = '\'';
    v[0x7] = 'e';
    v[0x8] = 'k';
    v[0x9] = 'e';
    v[0xa] = 'k';
    v[0xb] = '"';
    v[0xc] = 'A';
    v[0xd] = 'm';
    v[0xe] = 'z';
    v[0xf] = 'e';
    v[0x10] = 'b';
    v[0x11] = 'v';
    v[0x12] = '8';
    for (unsigned int i = 0; i < 0x13; ++i) {
        v[i] ^= ((i + 0x13) % m);
    }
    v[0x13] = '\0';
}

static inline void fill_java_lang_Object(char v[]) {
    // java/lang/Object
    static unsigned int m = 0;

    if (m == 0) {
        m = 13;
    } else if (m == 17) {
        m = 19;
    }

    v[0x0] = 'i';
    v[0x1] = 'e';
    v[0x2] = 's';
    v[0x3] = 'g';
    v[0x4] = '(';
    v[0x5] = 'd';
    v[0x6] = 'h';
    v[0x7] = 'd';
    v[0x8] = 'l';
    v[0x9] = '#';
    v[0xa] = 'O';
    v[0xb] = 'c';
    v[0xc] = 'h';
    v[0xd] = 'f';
    v[0xe] = 'g';
    v[0xf] = 'q';
    for (unsigned int i = 0; i < 0x10; ++i) {
        v[i] ^= ((i + 0x10) % m);
    }
    v[0x10] = '\0';
}

static jfieldID findMapField(JNIEnv *env, jclass classXposedBridge) {
    char signature[0x20];

    fill_sHookedMethodCallbacks_signature(signature);
    const char *mapName = findStaticMapName(env, classXposedBridge);
    if (mapName != NULL) {
#ifdef DEBUG
        LOGI("mapName: %s", mapName);
#endif
        return (*env)->GetStaticFieldID(env, classXposedBridge, mapName, signature);
    } else {
        char name[0x20];
        fill_sHookedMethodCallbacks(name); // 0x16
        jfieldID field = (*env)->GetStaticFieldID(env, classXposedBridge, mapName, signature);
        if ((*env)->ExceptionCheck(env)) {
            (*env)->ExceptionClear(env);
        }
        if (field == NULL) {
            debug(env, "cannot find sHookedMethodCallbacks in %s", classXposedBridge);
        }
        return field;
    }
}

static inline bool doClearHooksClass(JNIEnv *env, jclass classXposedBridge) {
    char v1[0x20], v2[0x20];
    bool antied = false;

    jfieldID field = findMapField(env, classXposedBridge);
    if (field == NULL) {
#ifdef DEBUG
        LOGI("cannot find static map");
#endif
        return false;
    }
    jobject map = (*env)->GetStaticObjectField(env, classXposedBridge, field);
    debug(env, "hooks: %s", map);

    fill_java_util_Map(v1); // 0xe
    jclass classMap = (*env)->FindClass(env, v1);
    if (map == NULL || !(*env)->IsInstanceOf(env, map, classMap)) {
        return false;
    }
    fill_values(v1); // 0x7
    fill_values_signature(v2); // 0x19
    jmethodID method = (*env)->GetMethodID(env, classMap, v1, v2);
    jobject values = (*env)->CallObjectMethod(env, map, method);

    fill_java_util_Collection(v1); // 0x15
    jclass classCollection = (*env)->FindClass(env, v1);
    fill_iterator(v1); // 0x9
    fill_iterator_signature(v2); // 0x17
    method = (*env)->GetMethodID(env, classCollection, v1, v2);
    jobject iterator = (*env)->CallObjectMethod(env, values, method);

    fill_java_util_Iterator(v1); // 0x13
    jclass classIterator = (*env)->FindClass(env, v1);
    fill_hasNext(v1); // 0x8
    fill_hasNext_signature(v2); // 0x4
    jmethodID hasNext = (*env)->GetMethodID(env, classIterator, v1, v2);
    fill_next(v1); // 0x5
    fill_next_signature(v2); // 0x15
    jmethodID next = (*env)->GetMethodID(env, classIterator, v1, v2);

    fill_java_lang_Object(v1);
    jclass classObject = (*env)->FindClass(env, v1);
    jobject emptyArray = (*env)->NewObjectArray(env, 0, classObject, NULL);
    jfieldID fieldElements = NULL;
    while ((*env)->CallBooleanMethod(env, iterator, hasNext)) {
        jobject hook = (*env)->CallObjectMethod(env, iterator, next);
        debug(env, "hook value: %s", hook);
        if (hook == NULL) {
            continue;
        }
        if (fieldElements == NULL) {
            jobject hookClass = (*env)->GetObjectClass(env, hook);
            char *name = findObjectArrayName(env, hookClass);
            if (name == NULL) {
                (*env)->DeleteLocalRef(env, hookClass);
                break;
            }
            fill_signature(v1);
            fieldElements = (*env)->GetFieldID(env, hookClass, name, v1);
            free(name);
            (*env)->DeleteLocalRef(env, hookClass);
        }
        (*env)->SetObjectField(env, hook, fieldElements, emptyArray);
        if ((*env)->ExceptionCheck(env)) {
            (*env)->ExceptionClear(env);
        } else if (!antied) {
            antied = true;
        }
        (*env)->DeleteLocalRef(env, hook);
    }

    (*env)->DeleteLocalRef(env, classIterator);
    (*env)->DeleteLocalRef(env, iterator);
    (*env)->DeleteLocalRef(env, classCollection);
    (*env)->DeleteLocalRef(env, values);
    (*env)->DeleteLocalRef(env, classMap);
    (*env)->DeleteLocalRef(env, map);

    return antied;
}

static inline void fill_de_robv_android_xposed_DexposedBridge(char v[]) {
    // de/robv/android/xposed/DexposedBridge
    static unsigned int m = 0;

    if (m == 0) {
        m = 31;
    } else if (m == 37) {
        m = 41;
    }

    v[0x0] = 'b';
    v[0x1] = 'b';
    v[0x2] = '\'';
    v[0x3] = '{';
    v[0x4] = 'e';
    v[0x5] = 'i';
    v[0x6] = 'z';
    v[0x7] = '"';
    v[0x8] = 'o';
    v[0x9] = 'a';
    v[0xa] = 't';
    v[0xb] = 'c';
    v[0xc] = '}';
    v[0xd] = 'z';
    v[0xe] = 'p';
    v[0xf] = ':';
    v[0x10] = 'n';
    v[0x11] = 'g';
    v[0x12] = 'w';
    v[0x13] = 'j';
    v[0x14] = '\x7f';
    v[0x15] = '\x7f';
    v[0x16] = '3';
    v[0x17] = 'Y';
    v[0x18] = '{';
    v[0x19] = 'x';
    v[0x1a] = 'q';
    v[0x1b] = 'm';
    v[0x1c] = 'p';
    v[0x1d] = 'a';
    v[0x1e] = 'a';
    v[0x1f] = 'D';
    v[0x20] = 'u';
    v[0x21] = 'a';
    v[0x22] = 'm';
    v[0x23] = 'm';
    v[0x24] = 'n';
    for (unsigned int i = 0; i < 0x25; ++i) {
        v[i] ^= ((i + 0x25) % m);
    }
    v[0x25] = '\0';
}

static bool doClearHooksCommon(JNIEnv *env, jobject classLoader, const char *name) {
    bool antied = false;
    jclass classXposedBridge = findLoadedClass(env, classLoader, name);
    if (classXposedBridge != NULL) {
#ifdef DEBUG
        LOGI("found %s", name);
#endif
        antied = doClearHooksClass(env, (jclass) classXposedBridge);
        (*env)->DeleteLocalRef(env, classXposedBridge);
    }
    return antied;
}

bool clearHooks(JNIEnv *env, jobject classLoader) {
    char v1[0x80];
    bool antied = false;

    debug(env, "clearHooks, classLoader: %s", classLoader);

    fill_me_weishu_epic_art2_EpicNative(v1);
    jclass epicNative = findLoadedClass(env, classLoader, v1);
    if (epicNative != NULL) {
        char *bridgeClass = findVoidStringName(env, epicNative);
#ifdef DEBUG
        LOGI("bridge class: %s", bridgeClass);
#endif
        if (bridgeClass != NULL) {
            antied |= doClearHooksCommon(env, classLoader, bridgeClass);
            free(bridgeClass);
        }
        (*env)->DeleteLocalRef(env, epicNative);
    }
    if (!antied) {
        fill_me_weishu_epic_art2_EpicBridge(v1);
        antied |= doClearHooksCommon(env, classLoader, v1);
    }
    if (!antied) {
        fill_de_robv_android_xposed_DexposedBridge(v1);
        antied |= doClearHooksCommon(env, classLoader, v1);
    }
    if (!antied) {
        fill_de_robv_android_xposed_XposedBridge(v1);
        antied |= doClearHooksCommon(env, classLoader, v1);
    }

    return antied;
}
