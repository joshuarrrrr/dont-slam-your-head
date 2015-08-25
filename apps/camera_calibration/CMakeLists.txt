CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_EXECUTABLE(camera_calibration
	"src/camera_calibration.cpp"
	)
TARGET_LINK_LIBRARIES(camera_calibration
	${OpenCV_LIBS}
	)
