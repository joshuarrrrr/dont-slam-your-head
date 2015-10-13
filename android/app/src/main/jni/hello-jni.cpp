
#include <string.h>
#include <jni.h>
#include "lsd-slam/test.hpp"
#include <string>

extern "C" {
jstring
Java_de_joshuareibert_dontslamyourhead_MainActivity_stringFromJNI(JNIEnv* env,
                                                 jobject thiz) {
    std::string test = helloFromLSDSLAM();
    return env->NewStringUTF(test.c_str());
}
}
