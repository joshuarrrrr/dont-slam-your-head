LOCAL_PATH := $(call my-dir)


include $(CLEAR_VARS)
LOCAL_MODULE := g2o_core
LOCAL_SRC_FILES := /home/joshua/Android/android-ndk-r10d/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/user/lib/libg2o_core.so
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := g2o_solver_csparse
LOCAL_SRC_FILES := /home/joshua/Android/android-ndk-r10d/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/user/lib/libg2o_solver_csparse.so
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := g2o_csparse_extension
LOCAL_SRC_FILES := /home/joshua/Android/android-ndk-r10d/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/user/lib/libg2o_csparse_extension.so
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := g2o_stuff
LOCAL_SRC_FILES := /home/joshua/Android/android-ndk-r10d/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/user/lib/libg2o_stuff.so
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := g2o_types_sba
LOCAL_SRC_FILES := /home/joshua/Android/android-ndk-r10d/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/user/lib/libg2o_types_sba.so
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := g2o_types_sim3
LOCAL_SRC_FILES := /home/joshua/Android/android-ndk-r10d/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/user/lib/libg2o_types_sim3.so
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := g2o_ext_csparse
LOCAL_SRC_FILES := /home/joshua/Android/android-ndk-r10d/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/user/lib/libg2o_ext_csparse.so
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := g2o_types_slam3d
LOCAL_SRC_FILES := /home/joshua/Android/android-ndk-r10d/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/user/lib/libg2o_types_slam3d.so
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := boost_thread
LOCAL_SRC_FILES := /home/joshua/git/dont-slam-your-head/android/app/src/main/jni/boost/lib/libboost_thread-gcc-mt-1_53.a
include $(PREBUILT_STATIC_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := boost_system
LOCAL_SRC_FILES := /home/joshua/git/dont-slam-your-head/android/app/src/main/jni/boost/lib/libboost_system-gcc-mt-1_53.a
include $(PREBUILT_STATIC_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := lsd-slam
LOCAL_SRC_FILES := lib/liblsdslam.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_SHARED_LIBRARIES := g2o_core g2o_solver_csparse
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE    := hello-jni
LOCAL_SRC_FILES := hello-jni.cpp
LOCAL_CFLAGS += -std=c++11
LOCAL_C_INCLUDES += /usr/include/eigen3
LOCAL_C_INCLUDES += $(LOCAL_PATH)/lsd_slam
LOCAL_C_INCLUDES += /home/joshua/Android/android-ndk-r10d/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/user/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/boost/include/
LOCAL_STATIC_LIBRARIES := boost_system boost_thread
LOCAL_SHARED_LIBRARIES := lsd-slam
include $(BUILD_SHARED_LIBRARY)