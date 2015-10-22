LOCAL_PATH := $(call my-dir)


include $(CLEAR_VARS)
include $(LOCAL_PATH)/g2o.mk


include $(CLEAR_VARS)
LOCAL_MODULE := boost_thread
LOCAL_SRC_FILES := /home/joshua/git/dont-slam-your-head/android/app/src/main/jni/boost/lib/libboost_thread-gcc-mt-1_53.a
include $(PREBUILT_STATIC_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := boost_system
LOCAL_SRC_FILES := /home/joshua/git/dont-slam-your-head/android/app/src/main/jni/boost/lib/libboost_system-gcc-mt-1_53.a
include $(PREBUILT_STATIC_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := lsd_slam
LOCAL_SRC_FILES := lib/liblsd_slam.so
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE    := lsd-jni
LOCAL_SRC_FILES := lsd-jni.cpp
LOCAL_CPPFLAGS += -std=c++11
LOCAL_C_INCLUDES += /usr/include/eigen3
LOCAL_C_INCLUDES += $(LOCAL_PATH)/lsd_slam
LOCAL_C_INCLUDES += /home/joshua/Android/android-ndk-r10d/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/user/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/boost/include/
LOCAL_STATIC_LIBRARIES := boost_system boost_thread
LOCAL_SHARED_LIBRARIES := lsd_slam
include $(BUILD_SHARED_LIBRARY)