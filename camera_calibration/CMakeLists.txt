cmake_minimum_required(VERSION 2.8)
project(dont_slam_your_head)

find_package(OpenCV REQUIRED)

add_executable(camera_calibration
	"src/camera_calibration.cpp"
	)
target_link_libraries(camera_calibration
	${OpenCV_LIBS}
	)
