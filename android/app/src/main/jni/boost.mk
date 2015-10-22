
include $(CLEAR_VARS)
LOCAL_MODULE := boost_thread
LOCAL_SRC_FILES := boost/lib/libboost_thread-gcc-mt-1_53.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := boost_system
LOCAL_SRC_FILES := boost/lib/libboost_system-gcc-mt-1_53.a
include $(PREBUILT_STATIC_LIBRARY)
