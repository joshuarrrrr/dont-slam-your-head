
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

	 bool setVideoCapture(cv::VideoCapture* cap);

	/**
	 * Thread main function.
	 */
	void operator()();

private:
	void setVideoResolution() const;

private:
	bool haveCalib;
	Undistorter* undistorter;
	cv::VideoCapture* capture;
};

}
