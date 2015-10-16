CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

PROJECT(dont_slam_your_head)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x") # ${SSE_FLAGS} -march=native")

FIND_PACKAGE(Eigen3 REQUIRED)
FIND_PACKAGE(G2O REQUIRED)
#FIND_PACKAGE(SuiteParse REQUIRED) # Apparently needed by g2o
#FIND_PACKAGE(OpenCV REQUIRED)

#SET(Boost_USE_STATIC_LIBS OFF)
#SET(Boost_USE_MULTITHREADED ON)
#SET(Boost_USE_STATIC_RUNTIME OFF)
#FIND_PACKAGE(Boost 1.45.0 COMPONENTS system thread program_options)

INCLUDE_DIRECTORIES(
	${EIGEN3_INCLUDE_DIR}
	${PROJECT_SOURCE_DIR}
	${PROJECT_SOURCE_DIR}/lsd_slam/
	${PROJECT_SOURCE_DIR}/thirdparty/Sophus
	/home/joshua/git/Boost-for-Android/build/include/boost-1_53
#	${CSPARSE_INCLUDE_DIR} #Has been set by SuiteParse
#	${CHOLMOD_INCLUDE_DIR} #Has been set by SuiteParse
#	${OpenCV_INCLUDE_DIRS}
	/home/joshua/Android/android-ndk-r10d/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/user/include
	/home/joshua/Android/android-ndk-r10d/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/user/include/EXTERNAL/csparse
)

ADD_SUBDIRECTORY(lsd_slam)
