
#include <string.h>
#include <jni.h>
#include "lsd_slam/DataStructures/Frame.h"
#include <Eigen/Dense>
#include <string>
#include <sstream>

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
    return env->NewStringUTF(txt.c_str());
}
}
