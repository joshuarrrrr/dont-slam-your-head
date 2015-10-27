#include <PrintOutput3DWrapper.hpp>

#include "DataStructures/Frame.h"
#include "GlobalMapping/KeyFrameGraph.h"
#include "sophus/sim3.hpp"

namespace lsd_slam
{

PrintOutput3DWrapper::PrintOutput3DWrapper() {};
PrintOutput3DWrapper::~PrintOutput3DWrapper() {};

void PrintOutput3DWrapper::publishKeyframeGraph(KeyFrameGraph* graph) {};

void PrintOutput3DWrapper::publishKeyframe(Frame* kf) {
	std::cout << "publishKeyframe" << std::endl;
	printPose(se3FromSim3(kf->getScaledCamToWorld()));
};

void PrintOutput3DWrapper::publishTrackedFrame(Frame* kf) {
	std::cout << "publishTrackedFrame" << std::endl;
	printPose(se3FromSim3(kf->getScaledCamToWorld()));
};

void PrintOutput3DWrapper::publishTrajectory(std::vector<Eigen::Matrix<float, 3, 1>> trajectory, std::string identifier) {
	std::cout << "PrintOutput3DWrapper::publishTrajectory" << std::endl;
};
void PrintOutput3DWrapper::publishTrajectoryIncrement(Eigen::Matrix<float, 3, 1> pt, std::string identifier) {
	std::cout << "PrintOutput3DWrapper::publishTrajectoryIncrement" << std::endl;
};

void PrintOutput3DWrapper::publishDebugInfo(Eigen::Matrix<float, 20, 1> data) {
	std::cout << "PrintOutput3DWrapper::publishDebugInfo" << std::endl;
};

void PrintOutput3DWrapper::printPose(SE3 const& pose) {
	Sophus::Quaternionf quat = pose.unit_quaternion().cast<float>();
	Eigen::Vector3f trans = pose.translation().cast<float>();
	std::cout << "  trans: ("
		<< trans[0] << ", " << trans[1] << ", " << trans[2]
		<< ")" << std::endl << "   rot: ("
		<< quat.x() << ", " << quat.y() << ", " << quat.z() << ", " << quat.w()
		<< ")" << std::endl;
}

}
