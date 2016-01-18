#!/bin/sh

cp -uv ./android/app/build/intermediates/bundles/armv7/debug/classes.jar ./unity/Assets/Plugins/Android/
cp -uv ./android/app/src/main/libs/armeabi-v7a/*.so ./unity/Assets/Plugins/Android/libs/armeabi-v7a/
cp -uv ./android/libraries/opencv/build/intermediates/bundles/release/classes.jar ./unity/Assets/Plugins/Android/OpenCV.jar

