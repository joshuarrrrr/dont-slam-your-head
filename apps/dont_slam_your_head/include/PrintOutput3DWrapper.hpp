
#pragma once

#include <iostream>

#include <lsd_slam/IOWrapper/Output3DWrapper.h>

namespace lsd_slam
{

class PrintOutput3DWrapper : public Output3DWrapper
{
public:
	PrintOutput3DWrapper();
	~PrintOutput3DWrapper();

	/*virtual*/ void publishKeyframeGraph(KeyFrameGraph* graph);

	// publishes a keyframe. if that frame already existis, it is overwritten, otherwise it is added.
	/*virtual*/ void publishKeyframe(Frame* kf);

	// published a tracked frame that did not become a keyframe (yet; i.e. has no depth data)
	/*virtual*/ void publishTrackedFrame(Frame* kf);

	// publishes graph and all constraints, as well as updated KF poses.
	/*virtual*/ void publishTrajectory(std::vector<Eigen::Matrix<float, 3, 1>> trajectory, std::string identifier);
	/*virtual*/ void publishTrajectoryIncrement(Eigen::Matrix<float, 3, 1> pt, std::string identifier);

	/*virtual*/ void publishDebugInfo(Eigen::Matrix<float, 20, 1> data);
};

}
