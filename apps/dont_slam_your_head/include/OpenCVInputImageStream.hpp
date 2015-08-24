
#pragma once

#include <iostream>

#include <lsd_slam/IOWrapper/InputImageStream.h>
#include <lsd_slam/util/Undistorter.h>

#include <boost/thread.hpp>
#include <opencv2/opencv.hpp>

namespace lsd_slam
{

class OpenCVInputImageStream : public InputImageStream
{
public:
	OpenCVInputImageStream();
	~OpenCVInputImageStream();

	/**
	 * Starts the thread.
	 */
	/*virtual*/ void run();

	/*virtual*/ void setCalibration(std::string file);

	/**
	 * Thread main function.
	 */
	void operator()();

private:
	bool haveCalib;
	Undistorter* undistorter;

	std::string vid_channel;

	int lastSEQ;

	cv::VideoCapture capture;
};

}
