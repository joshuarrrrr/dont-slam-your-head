#include <OpenCVInputImageStream.hpp>

namespace lsd_slam
{

OpenCVInputImageStream::OpenCVInputImageStream() {
	// wait for cam calib
	width_ = height_ = 0;

	// imagebuffer
	imageBuffer = new NotifyBuffer<TimestampedMat>(8);
	undistorter = 0;
	lastSEQ = 0;

	haveCalib = false;

	capture.open(0);
}

OpenCVInputImageStream::~OpenCVInputImageStream() {
	delete imageBuffer;
}

void OpenCVInputImageStream::run() {
	boost::thread thread(boost::ref(*this));
}

void OpenCVInputImageStream::setCalibration(std::string file) {
	if (file == "") {
		std::cerr << "No calibration file given!" << std::endl;
		exit(0);
	} else {
		undistorter = Undistorter::getUndistorterForFile(file.c_str());

		if (undistorter == 0) {
			std::cerr << "Failed to read camera calibration from file... wrong syntax?" << std::endl;
			exit(0);
		}

		fx_ = undistorter->getK().at<double>(0, 0);
		fy_ = undistorter->getK().at<double>(1, 1);
		cx_ = undistorter->getK().at<double>(2, 0);
		cy_ = undistorter->getK().at<double>(2, 1);

		width_ = undistorter->getOutputWidth();
		height_ = undistorter->getOutputHeight();

		capture.set(CV_CAP_PROP_FRAME_WIDTH, width_);
		capture.set(CV_CAP_PROP_FRAME_HEIGHT, height_);
	}

	haveCalib = true;
}

void OpenCVInputImageStream::operator()() {
	if (!haveCalib) {
		std::cerr << "no calibration" << std::endl;
		return;
	}
	if (!capture.isOpened())
	{
		std::cerr << "NO valid camera capture" << std::endl;
		return;
	}
	while (1)
	{
		TimestampedMat bufferItem;
		bufferItem.timestamp = Timestamp::now();
		//IplImage* frame;
		cv::Mat frame;
		capture >> frame;
		if (undistorter != 0)
		{
			assert(undistorter->isValid());
			undistorter->undistort(frame, bufferItem.data);
		}
		else
		{
			bufferItem.data = frame;
		}
		//bufferItem.data = cv::Mat(frame, true);
		imageBuffer->pushBack(bufferItem);
	}
	exit(0);
}

}
