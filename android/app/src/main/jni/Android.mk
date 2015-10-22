LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
include $(LOCAL_PATH)/g2o/Android.mk

include $(CLEAR_VARS)
include $(LOCAL_PATH)/boost/Android.mk

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
LOCAL_C_INCLUDES += $(LOCAL_PATH)/g2o/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/boost/include/
LOCAL_STATIC_LIBRARIES := boost_system boost_thread
LOCAL_SHARED_LIBRARIES := lsd_slam
include $(BUILD_SHARED_LIBRARY)
