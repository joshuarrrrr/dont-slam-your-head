CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

include_directories(".")

ADD_LIBRARY(lsd-slam SHARED "test.cpp")

install(
	TARGETS lsd-slam
	LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/android/app/src/main/jni/lib
	DESTINATION ${PROJECT_SOURCE_DIR}/android/app/src/main/jni/lib
	)
install(
	FILES "test.hpp"
	DESTINATION ${PROJECT_SOURCE_DIR}/android/app/src/main/jni/lsd-slam
	)
