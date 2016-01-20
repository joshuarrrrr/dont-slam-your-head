
#include <android/log.h>
#include <jni.h>
#include <sstream>
#include <ctime>

#include <lsd_slam/LiveSLAMWrapper.h>
#include <lsd_slam/IOWrapper/Timestamp.h>
#include <lsd_slam/util/Undistorter.h>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#define  LOG_TAG    "lsd-jni.cpp"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static lsd_slam::LiveSLAMWrapper* slam;
static lsd_slam::UndistorterOpenCV* undistorter;
static int frameCount = 0;


extern "C" {
JNIEXPORT void Java_de_joshuareibert_dontslamyourhead_MainActivity_initSLAM(
        JNIEnv* env, jobject thiz) {
    undistorter = new lsd_slam::UndistorterOpenCV(
            1100.66, 1100.66, 639.5, 359.5, 0.0737079, -0.0529861, 0, 0,
            1280, 720,
            "crop",
            320, 240);
    slam = new lsd_slam::LiveSLAMWrapper(undistorter);
}

JNIEXPORT void Java_de_joshuareibert_dontslamyourhead_MainActivity_updateSLAM(
        JNIEnv* env, jobject thiz,
        jlong grayImgAddress, jlong rgbaImgAddress, jlong depthImgAddress)
{
    cv::Mat& image = *(cv::Mat*)grayImgAddress;
    cv::Mat& out_image = *(cv::Mat*)rgbaImgAddress;
    cv::Mat& depth_image = *(cv::Mat*)depthImgAddress;
    cv::Mat undist_image;
    undistorter->undistort(image, undist_image);
    SE3 pose = slam->newImageCallback(undist_image, depth_image, lsd_slam::Timestamp::now());

    #ifdef STORE_DEBUG_IMAGES
    ++frameCount;
    if (frameCount % 50 == 0) {
        std::ostringstream ss;
        ss << frameCount;
        std::time_t rawtime;
        std::tm* timeinfo;
        char buffer [80];

        std::time(&rawtime);
        timeinfo = std::localtime(&rawtime);

        std::strftime(buffer,80,"%Y%m%d%H%M%S",timeinfo);
        std::string datestr(buffer, 14);
        std::string filename = "/sdcard/lsdslam/image" + datestr;
        cv::imwrite(filename + "_distorted.png", image);
        cv::imwrite(filename + "_undistorted.png", undist_image);
        LOGD("stored frame#%d on disk", frameCount);
    }
    #endif

    // if there is a depth image, set is as output image
    if (depth_image.type() > 0 && !depth_image.empty()) {
        cv::Mat depth_image_rgba;
        cv::resize(depth_image, depth_image_rgba, out_image.size());
        cv::cvtColor(depth_image_rgba, out_image, CV_RGB2RGBA);
    }

    Eigen::Vector3f trans = pose.translation().cast<float>();
    Sophus::Quaternionf quat = pose.unit_quaternion().cast<float>();

    jclass activity = env->FindClass("de/joshuareibert/dontslamyourhead/MainActivity");
    if (activity == NULL) {
        LOGE("activity class not found!");
        return;
    }
    jmethodID trans_setter = env->GetMethodID(activity, "setTranslation", "(FFF)V");
    if (trans_setter == NULL) {
        LOGE("setTranslation method not found!");
        return;
    }
    jmethodID rot_setter = env->GetMethodID(activity, "setRotation", "(FFFF)V");
    if (rot_setter == NULL) {
        LOGE("setRotation method not found!");
        return;
    }
    env->CallObjectMethod(thiz, trans_setter, trans[0], trans[1], trans[2]);
    env->CallObjectMethod(thiz, rot_setter, quat.x(), quat.y(), quat.z(), quat.w());
}

JNIEXPORT void Java_de_joshuareibert_dontslamyourhead_MainActivity_resetSLAM(
        JNIEnv* env, jobject thiz) {
    slam->requestReset();
}
}
