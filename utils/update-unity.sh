#!/bin/sh

cp -u ./android/app/build/intermediates/bundles/armv7/debug/classes.jar ./unity/Assets/Plugins/Android/
cp -u ./android/app/src/main/libs/armeabi-v7a/*.so ./unity/Assets/Plugins/Android/libs/armeabi-v7a/
cp -u ./android/libraries/opencv/build/intermediates/bundles/release/classes.jar ./unity/Assets/Plugins/Android/OpenCV.jar

