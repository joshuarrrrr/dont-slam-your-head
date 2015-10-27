FILE(GLOB_RECURSE LSD_SOURCES "*/*.cpp")
LIST(APPEND LSD_SOURCES
	"LiveSLAMWrapper.cpp"
	"SlamSystem.cpp"
	)

#SET(LSD_SOURCES
#	DataStructures/Frame.cpp
#	DataStructures/FrameMemory.cpp
#	DataStructures/FramePoseStruct.cpp
#	Tracking/TrackingReference.cpp
#	util/settings.cpp
#	)

FILE(GLOB_RECURSE LSD_HEADERS "*.h")

FILE(GLOB_RECURSE Boost_LIBRARIES
	"${PROJECT_SOURCE_DIR}/android/app/src/main/jni/boost/lib/libboost_*.a"
	)

set(G2O_LIBRARIES
	${PROJECT_SOURCE_DIR}/android/app/src/main/jni/g2o/lib/libg2o_core.so
	${PROJECT_SOURCE_DIR}/android/app/src/main/jni/g2o/lib/libg2o_ext_csparse.so
	${PROJECT_SOURCE_DIR}/android/app/src/main/jni/g2o/lib/libg2o_solver_csparse.so
	${PROJECT_SOURCE_DIR}/android/app/src/main/jni/g2o/lib/libg2o_csparse_extension.so
	${PROJECT_SOURCE_DIR}/android/app/src/main/jni/g2o/lib/libg2o_stuff.so
	${PROJECT_SOURCE_DIR}/android/app/src/main/jni/g2o/lib/libg2o_types_sba.so
	${PROJECT_SOURCE_DIR}/android/app/src/main/jni/g2o/lib/libg2o_types_sim3.so
	)

ADD_LIBRARY(lsd_slam SHARED ${LSD_SOURCES})
TARGET_LINK_LIBRARIES(lsd_slam
	${FABMAP_LIB}
	#${CSPARSE_LIBRARY}
	#${G2O_CORE_LIBRARY}
	#${G2O_EXT_CSPARSE}
	#${G2O_SOLVER_CSPARSE}
	#${G2O_SOLVER_CSPARSE_EXTENSION}
	#${G2O_STUFF_LIBRARY}
	#${G2O_TYPES_SBA}
	#${G2O_TYPES_SIM3}
	${G2O_LIBRARIES}
	${Boost_LIBRARIES}
	${OpenCV_LIBS}
	)

install(
	TARGETS lsd_slam
	LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/android/app/src/main/jni/lib
	DESTINATION ${PROJECT_SOURCE_DIR}/android/app/src/main/jni/lib
	)

install(
	DIRECTORY ${PROJECT_SOURCE_DIR}/lsd_slam
	DESTINATION ${PROJECT_SOURCE_DIR}/android/app/src/main/jni
	FILES_MATCHING PATTERN "*.h"
	)

install(
	DIRECTORY ${PROJECT_SOURCE_DIR}/thirdparty/Sophus/sophus
	DESTINATION ${PROJECT_SOURCE_DIR}/android/app/src/main/jni
	FILES_MATCHING PATTERN "*.hpp"
	)
