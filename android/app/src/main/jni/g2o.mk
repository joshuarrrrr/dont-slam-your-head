
include $(CLEAR_VARS)
LOCAL_MODULE := g2o_core
LOCAL_SRC_FILES := g2o/lib/libg2o_core.so
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := g2o_solver_csparse
LOCAL_SRC_FILES := g2o/lib/libg2o_solver_csparse.so
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := g2o_csparse_extension
LOCAL_SRC_FILES := g2o/lib/libg2o_csparse_extension.so
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := g2o_stuff
LOCAL_SRC_FILES := g2o/lib/libg2o_stuff.so
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := g2o_types_sba
LOCAL_SRC_FILES := g2o/lib/libg2o_types_sba.so
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := g2o_types_sim3
LOCAL_SRC_FILES := g2o/lib/libg2o_types_sim3.so
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := g2o_ext_csparse
LOCAL_SRC_FILES := g2o/lib/libg2o_ext_csparse.so
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := g2o_types_slam3d
LOCAL_SRC_FILES := g2o/lib/libg2o_types_slam3d.so
include $(PREBUILT_SHARED_LIBRARY)
