
#include <android/log.h>
#include <jni.h>
#include <sstream>
#include <ctime>
#include <queue>
#include <vector>
#include <functional>

#include <Eigen/Core>
#include <Eigen/Geometry>
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

// values for 320x240 input images
/*static float in_width = 320;
static float in_height = 240;
 static float fx = 275.831f;
static float fy = 275.26f;
static float cx = 159.32f;
static float cy = 121.474f;
static float k1 = 0.0454102f;
static float k2 = 0.225756f;
static float p1 = 0.00056932f;
static float p2 = 0.000524407f;*/

// values for 640x480 input images
static unsigned int in_width = 640;
static unsigned int in_height = 480;
static float in_fx = 554.342f;
static float in_fy = 553.345f;
static float in_cx = 320.898f;
static float in_cy = 243.149f;
static float in_k1 = 0.0781625f;
static float in_k2 = -0.243653f;
static float in_p1 = -0.000555435f;
static float in_p2 = -0.000276287f;

// values for the undistored images
// TODO: get these values from the undistorter
static unsigned int out_width = 320;
static unsigned int out_height = 240;
static float out_fx = 276.011f;
static float out_fy = 277.207f;
static float out_cx = 159.893f;
static float out_cy = 120.989f;
static float fxi = 1.0 / out_fx;
static float fyi = 1.0 / out_fy;
static float cxi = -out_cx / out_fx;
static float cyi = -out_cy / out_fy;


static int numPoints = 500;
static float* points= nullptr;
static Sim3 camToWorld;


void getBestPoints() {
    typedef std::pair<float, int> P;
    std::priority_queue<P, std::vector<P>, std::greater<P>> q;
    for (int i = 0; i < out_width * out_height; ++i) {
        q.push(std::pair<float, int>(idepthVar[i], i));
    }
    for (int i = 0; i < numPoints; ++i) {
        int idx = q.top().second;
        int x = idx % out_width;
        int y = idx / out_height;
        float depth = 1.0 / idepthMap[idx];
        Sophus::Vector3f pos((x * fxi + cxi) * depth, (y * fyi + cyi) * depth, depth);
        Sophus::Vector3f world_pos = camToWorld.cast<float>() * pos;
        points[i * 3] = world_pos[0];
        points[i * 3 + 1] = world_pos[1];
        points[i * 3 + 2] = world_pos[2];

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
    undistorter = new lsd_slam::UndistorterOpenCV(
            in_fx, in_fy, in_cx, in_cy, in_k1, in_k2, in_p1, in_p2,
            in_width, in_height,
            "crop",
            out_width, out_height);
    slam = new lsd_slam::LiveSLAMWrapper(undistorter);
    idepthMap = new float[out_width * out_height];
    idepthVar = new float[out_width * out_height];
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
    env->SetFloatArrayRegion(jiDepthMap, 0, out_width * out_height, idepthMap);
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

    //Eigen::Vector3f trans = Eigen::AngleAxisf(M_PI, Eigen::Vector3f::UnitZ()) * pose.translation().cast<float>();
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

JNIEXPORT void Java_de_joshuareibert_dontslamyourhead_MainActivity_exportPointCloud(
        JNIEnv* env, jobject thiz) {
    slam->dumpMap("/sdcard/lsdslam/mapdump");
}
}
