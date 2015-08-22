FILE(GLOB_RECURSE APP_SOURCES "*.cpp")

ADD_EXECUTABLE(dont_slam_your_head ${APP_SOURCES})
ADD_DEPENDENCIES(dont_slam_your_head lsdslam)
TARGET_LINK_LIBRARIES(dont_slam_your_head
	lsdslam
	${Boost_LIBRARIES}
	)
