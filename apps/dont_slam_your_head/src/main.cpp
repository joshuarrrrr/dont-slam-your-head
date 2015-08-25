#include <iostream>
#include <string>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <opencv2/opencv.hpp>

#include <lsd_slam/LiveSLAMWrapper.h>

#include <lsd_slam/IOWrapper/InputImageStream.h>
#include <lsd_slam/IOWrapper/Output3DWrapper.h>

#include <OpenCVInputImageStream.hpp>
#include <PrintOutput3DWrapper.hpp>

int main(int argc, char* argv[]) {
	try {
		po::options_description desc("Allowed options");
		desc.add_options()
			("help,h", "display help message")
			("calibration_file,f",
				po::value<std::string>()->default_value("config/calib.txt"),
				"file containing calibration params")
			("camera_id,c",
				po::value<int>()->default_value(0),
				"id of the camera to use: e.g. 0 for /dev/video0")
			;
		po::variables_map vm;
        po::store(parse_command_line(argc, argv, desc), vm);

        // print help message
        if (vm.count("help")) {
            std::cout << "Usage: " << argv[0] << std::endl << desc << std::endl;
            return 0;
        }

        // create video capture
        cv::VideoCapture* capture = new cv::VideoCapture(
        	(vm["camera_id"].as<int>())
        	);

        // create and configure input
        lsd_slam::OpenCVInputImageStream* imageStream =
        	new lsd_slam::OpenCVInputImageStream();
        imageStream->setCalibration(vm["calibration_file"].as<std::string>());
        imageStream->setVideoCapture(capture);
        imageStream->run();

        // create and configure output
        lsd_slam::Output3DWrapper* outputWrapper =
        	new lsd_slam::PrintOutput3DWrapper();

        // create slam system and go into main loop
        lsd_slam::LiveSLAMWrapper slam(imageStream, outputWrapper);
        slam.Loop();

	} catch(std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
        return 1;
	}

	return 0;
}
