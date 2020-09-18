# Xposed Detector

static library prefab to detect xposed and clear hooks.

This library is based on the [genuine](https://github.com/brevent/genuine).

## Integration

Gradle:

```gradle
implementation 'io.github.vvb2060.ndk:xposeddetector:1.0'
```

This library is [Prefab](https://google.github.io/prefab/), so you will need to enable it in your project (Android Gradle Plugin 4.1+):

```gradle
android {
    ...
    buildFeatures {
        ...
        prefab true
    }
}
```

## Usage

### ndk-build

you can use `xposed_detector` in your `Android.mk`. 
For example, if your application defines `libapp.so` and it uses `xposed_detector`, your `Android.mk` file should include the following:

```makefile
include $(CLEAR_VARS)
LOCAL_MODULE           := app
LOCAL_SRC_FILES        := app.cpp
LOCAL_STATIC_LIBRARIES := xposed_detector
include $(BUILD_SHARED_LIBRARY)

# If you don't need your project to build with NDKs older than r21, you can omit
# this block.
ifneq ($(call ndk-major-at-least,21),true)
    $(call import-add-path,$(NDK_GRADLE_INJECTED_IMPORT_PATH))
endif

$(call import-module,prefab/xposeddetector)
```

### CMake

you can use `xposed_detector` in your `CMakeLists.txt`. 
For example, if your application defines `libapp.so` and it uses `xposed_detector`, your `CMakeLists.txt` file should include the following:

```cmake
add_library(app SHARED app.cpp)

# Add these two lines.
find_package(xposeddetector REQUIRED CONFIG)
target_link_libraries(app xposeddetector::xposed_detector)
```

## Sample application

Use the `gradlew :app:iR` command to install sample app, or download [prebuilt apk](https://github.com/vvb2060/XposedDetector/releases/latest).
