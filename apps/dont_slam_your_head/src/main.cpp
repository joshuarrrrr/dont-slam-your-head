#include <lsd_slam/LiveSLAMWrapper.h>

#include <lsd_slam/IOWrapper/InputImageStream.h>
#include <lsd_slam/IOWrapper/Output3DWrapper.h>

#include <OpenCVInputImageStream.hpp>
#include <PrintOutput3DWrapper.hpp>

int main() {
	// create and configure input
	lsd_slam::InputImageStream* imageStream =
		new lsd_slam::OpenCVInputImageStream();
	imageStream->run();

	// create and configure output
	lsd_slam::Output3DWrapper* outputWrapper =
		new lsd_slam::PrintOutput3DWrapper();

	// create slam system and go into main loop
	lsd_slam::LiveSLAMWrapper slam(imageStream, outputWrapper);
	slam.Loop();
	return 0;
}
