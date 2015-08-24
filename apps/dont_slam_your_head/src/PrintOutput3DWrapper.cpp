#include <PrintOutput3DWrapper.hpp>

namespace lsd_slam
{

PrintOutput3DWrapper::PrintOutput3DWrapper() {};
PrintOutput3DWrapper::~PrintOutput3DWrapper() {};

void PrintOutput3DWrapper::publishKeyframeGraph(KeyFrameGraph* graph) {
	std::cout << "PrintOutput3DWrapper::publishKeyframeGraph" << std::endl;
};

void PrintOutput3DWrapper::publishKeyframe(Frame* kf) {
	std::cout << "PrintOutput3DWrapper::publishKeyframe" << std::endl;
};

void PrintOutput3DWrapper::publishTrackedFrame(Frame* kf) {
	std::cout << "PrintOutput3DWrapper::publishTrackedFrame" << std::endl;
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

}
