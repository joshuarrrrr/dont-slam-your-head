
#include <jni.h>
#include <lsd_slam/util/EigenCoreInclude.h>
#include <lsd_slam/DataStructures/Frame.h>

extern "C" {
jstring
Java_de_joshuareibert_dontslamyourhead_MainActivity_stringFromJNI(JNIEnv* env,
                                                 jobject thiz) {
    unsigned char* img = new unsigned char();
    lsd_slam::Frame frame(0, 320, 240, Eigen::Matrix3f(), 0, img);
    return env->NewStringUTF("Yay! It worked.");
}
}
