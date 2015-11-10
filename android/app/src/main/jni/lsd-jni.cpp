
#include <android/log.h>
#include <jni.h>

#include <lsd_slam/LiveSLAMWrapper.h>
#include <lsd_slam/IOWrapper/Timestamp.h>
#include <lsd_slam/util/Undistorter.h>

#define  LOG_TAG    "lsd-jni.cpp"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static lsd_slam::LiveSLAMWrapper* slam;
static lsd_slam::UndistorterOpenCV* undistorter;


extern "C" {
JNIEXPORT void Java_de_joshuareibert_dontslamyourhead_MainActivity_initSLAM(
        JNIEnv* env, jobject thiz) {
    undistorter = new lsd_slam::UndistorterOpenCV(
            2836.06, 2836.06, 1223.5, 1631.5, 0.0781421, -0.0862457, 0, 0,
            1280, 768,
            "crop",
            320, 240);
    slam = new lsd_slam::LiveSLAMWrapper(undistorter);
}

JNIEXPORT void Java_de_joshuareibert_dontslamyourhead_MainActivity_updateSLAM(
        JNIEnv* env, jobject thiz, jlong matAddress) {
    cv::Mat& image = *(cv::Mat*)matAddress;
    cv::Mat undist_image;
    undistorter->undistort(image, undist_image);
    slam->newImageCallback(undist_image, lsd_slam::Timestamp::now());
}

JNIEXPORT void Java_de_joshuareibert_dontslamyourhead_MainActivity_resetSLAM(
        JNIEnv* env, jobject thiz) {
    slam->resetAll();
}
}
