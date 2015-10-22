
#include <string.h>
#include <jni.h>
#include <lsd_slam/DataStructures/Frame.h>
#include <Eigen/Dense>
#include <string>
#include <sstream>

#include <opencv2/opencv.hpp>

std::string const doubleToString(double d) {
    std::ostringstream ostr;
    ostr << d;
    return ostr.str();
}

extern "C" {
jstring
Java_de_joshuareibert_dontslamyourhead_MainActivity_stringFromJNI(JNIEnv* env,
                                                 jobject thiz) {
    const unsigned char* image = new unsigned char();
    lsd_slam::Frame frame(0, 320, 240, Eigen::Matrix3f(), 27.5, image);
    std::string txt = "Yay! It works and returns '" + doubleToString(frame.timestamp()) + "'";

    cv::Mat mat = cv::Mat(1, 1, CV_64F, 3.5);
    txt += "\nAnd there is even a cv::Mat with the value '" + doubleToString(mat.at<double>(0,0))
            + "' at the first element!";

    return env->NewStringUTF(txt.c_str());
}
}