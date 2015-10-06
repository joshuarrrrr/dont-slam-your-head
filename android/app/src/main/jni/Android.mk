LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := lsd-slam
LOCAL_SRC_FILES := liblsd-slam.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := hello-jni
LOCAL_SRC_FILES := hello-jni.cpp
LOCAL_SHARED_LIBRARIES := lsd-slam
include $(BUILD_SHARED_LIBRARY)