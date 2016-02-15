
#include <android/log.h>
#include <jni.h>
#include <sstream>
#include <ctime>
#include <queue>
#include <vector>
#include <functional>

#include <Eigen/Core>
#include <sophus/sim3.hpp>

#include <lsd_slam/LiveSLAMWrapper.h>
#include <lsd_slam/IOWrapper/Timestamp.h>
#include <lsd_slam/util/Undistorter.h>
#include <lsd_slam/util/SophusUtil.h>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#define  LOG_TAG    "lsd-jni.cpp"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

//#define STORE_DEBUG_IMAGES
//#define DEBUG_PRINTS

static lsd_slam::LiveSLAMWrapper* slam;
static lsd_slam::UndistorterOpenCV* undistorter;
static int frameCount = 0;
static float* idepthMap = nullptr;
static float* idepthVar = nullptr;
static int width = 0;
static int height = 0;
static float fx = 1100.66f;
static float fy = 1100.66f;
static float cx = 639.5f;
static float cy = 359.5f;
static float fxi;
static float fyi;
static float cxi;
static float cyi;
static int numPoints = 500;
static float* points= nullptr;
static Sim3 camToWorld;


void getBestPoints() {
    typedef std::pair<float, int> P;
    std::priority_queue<P, std::vector<P>, std::greater<P>> q;
    for (int i = 0; i < width * height; ++i) {
        q.push(std::pair<float, int>(idepthVar[i], i));
    }
    for (int i = 0; i < numPoints; ++i) {
        int idx = q.top().second;
        int x = idx % width;
        int y = idx / height;
        float depth = 1 / idepthMap[idx];
        Sophus::Vector3f pos = camToWorld.cast<float>() * (Sophus::Vector3f((x * fxi + cxi), (y * fyi + cyi), 1) * depth);
        //Eigen::Vector3f pos = Eigen::Vector3f(x * fxi + cxi, y * fyi + cyi, 1.0f) * depth;
        points[i * 3] = pos[0];
        points[i * 3 + 1] = pos[1];
        points[i * 3 + 2] = pos[2];

        #ifdef DEBUG_PRINTS
        // debug log of five points with lowest variance, TODO remove
        if (i < 5) {
            LOGD("%d: index[%d] = %f => (%.3f, %.3f, %.3f)", i, idx, idepthVar[idx],
                 pos.x(), pos.y(), pos.z());
        }
        #endif

        q.pop();
    }
}


extern "C" {
JNIEXPORT void Java_de_joshuareibert_dontslamyourhead_MainActivity_initSLAM(
        JNIEnv* env, jobject thiz,
        int w, int h) {
    width = w;
    height = h;
    fxi = 1 / fx;
    fyi = 1 / fy;
    cxi = -cx / fx;
    cyi = -cy / fy;
    undistorter = new lsd_slam::UndistorterOpenCV(
            fx, fy, cx, cy, 0.0737079, -0.0529861, 0, 0,
            1280, 720,
            "crop",
            width, height);
    slam = new lsd_slam::LiveSLAMWrapper(undistorter);
    idepthMap = new float[width * height];
    idepthVar = new float[width * height];
    points = new float[numPoints * 3];
}

JNIEXPORT void Java_de_joshuareibert_dontslamyourhead_MainActivity_updateSLAM(
        JNIEnv* env, jobject thiz,
        jlong grayImgAddress, jlong rgbaImgAddress, jlong depthImgAddress,
        jfloatArray jiDepthMap, jfloatArray jPoints)
{
    cv::Mat& image = *(cv::Mat*)grayImgAddress;
    cv::Mat& out_image = *(cv::Mat*)rgbaImgAddress;
    cv::Mat& depth_image = *(cv::Mat*)depthImgAddress;
    cv::Mat undist_image;
    undistorter->undistort(image, undist_image);
    SE3 pose = slam->newImageCallback(undist_image, idepthMap, idepthVar, camToWorld, lsd_slam::Timestamp::now());
    getBestPoints();
    env->SetFloatArrayRegion(jiDepthMap, 0, width * height, idepthMap);
    env->SetFloatArrayRegion(jPoints, 0, numPoints * 3, points);

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
        //if (depth_image.type() > 0 && !depth_image.empty())
        //    cv::imwrite(filename + "_depth.png", depth_image);
        LOGD("stored frame#%d on disk", frameCount);
    }
    #endif

    // if there is a depth image, set is as output image
    //if (depth_image.type() > 0 && !depth_image.empty()) {
    //    cv::Mat depth_image_rgba;
    //    cv::resize(depth_image, depth_image_rgba, out_image.size());
    //    cv::cvtColor(depth_image_rgba, out_image, CV_RGB2RGBA);
    //}

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
