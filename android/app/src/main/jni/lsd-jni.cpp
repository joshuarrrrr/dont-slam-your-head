
#include <jni.h>
#include <lsd_slam/LiveSLAMWrapper.h>
#include <lsd_slam/IOWrapper/Timestamp.h>

static lsd_slam::LiveSLAMWrapper slam;

extern "C" {
JNIEXPORT void Java_de_joshuareibert_dontslamyourhead_MainActivity_updateSLAM(
        JNIEnv* env, jobject thiz, jlong matAddress) {
    cv::Mat& image = *(cv::Mat*)matAddress;
    slam.newImageCallback(image, lsd_slam::Timestamp::now());
}
}
