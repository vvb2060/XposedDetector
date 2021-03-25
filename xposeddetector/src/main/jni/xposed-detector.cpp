#include "include/xposed-detector.h"
#include "classloader.h"
#include "obfs-string.h"
#include "xposed.h"

int xposed_status = NO_XPOSED;

int get_xposed_status(JNIEnv *env, int sdk) {
    checkClassLoader((C_JNIEnv *) env, sdk);

    if (xposed_status == NO_XPOSED) {
        return xposed_status;
    }

    checkCallStack((C_JNIEnv *) env);
    return xposed_status;
}
