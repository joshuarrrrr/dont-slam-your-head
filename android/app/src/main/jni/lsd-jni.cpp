
#include <android/log.h>
#include <jni.h>

#include <lsd_slam/LiveSLAMWrapper.h>
#include <lsd_slam/IOWrapper/Timestamp.h>

#define  LOG_TAG    "lsd-jni.cpp"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static lsd_slam::LiveSLAMWrapper slam;

extern "C" {
JNIEXPORT void Java_de_joshuareibert_dontslamyourhead_MainActivity_updateSLAM(
        JNIEnv* env, jobject thiz, jlong matAddress) {
    cv::Mat& image = *(cv::Mat*)matAddress;
    slam.newImageCallback(image, lsd_slam::Timestamp::now());
}
}
