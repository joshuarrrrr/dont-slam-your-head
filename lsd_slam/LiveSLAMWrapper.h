/**
* This file is part of LSD-SLAM.
*
* Copyright 2013 Jakob Engel <engelj at in dot tum dot de> (Technical University of Munich)
* For more information see <http://vision.in.tum.de/lsdslam>
*
* LSD-SLAM is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* LSD-SLAM is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with LSD-SLAM. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <iostream>
#include <fstream>
#include <chrono>

#include "IOWrapper/Timestamp.h"
#include "IOWrapper/NotifyBuffer.h"
#include "IOWrapper/TimestampedObject.h"
#include "util/SophusUtil.h"
#include "util/Undistorter.h"

namespace cv {
	class Mat;
}



namespace lsd_slam
{

class SlamSystem;
class LiveSLAMWrapperROS;
class InputImageStream;
class Output3DWrapper;


struct LiveSLAMWrapper : public Notifiable
{
friend class LiveSLAMWrapperROS;
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	LiveSLAMWrapper(Undistorter* undistorter);

	/** Destructor. */
	~LiveSLAMWrapper();


	/** Runs the main processing loop. Will never return. */
	//void Loop();

	/** Requests a reset from a different thread. */
	void requestReset();

	/** Resets everything, starting the odometry from the beginning again. */
	void resetAll();

	/** Callback function for new RGB images. */
	SE3 newImageCallback(const cv::Mat& grayImg, float* depthMap, float* depthVar, Sim3& crrntKeyFrameCamToWorld, Timestamp imgTime);

	/** Writes the given time and pose to the outFile. */
	void logCameraPose(const SE3& camToWorld, double time);

	void dumpMap(std::string const& folder) const;


	inline SlamSystem* getSlamSystem() {return monoOdometry;}

private:

	// initialization stuff
	bool isInitialized;

	Undistorter* undistorter;

	// monoOdometry
	SlamSystem* monoOdometry;

	std::string outFileName;
	std::ofstream* outFile;

	float fx, fy, cx, cy;
	int width, height;


	int imageSeqNumber;

};

}
