#include "include/xposed-detector.h"
#include "classloader.h"

int xposed_status = NO_XPOSED;

int get_xposed_status(JNIEnv *env, int sdk) {
    checkClassLoader(env, sdk);
    return xposed_status;
}
