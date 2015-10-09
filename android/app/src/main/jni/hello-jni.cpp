
#include <string.h>
#include <jni.h>
#include <lsdtest.hpp>
#include <string>

extern "C" {
jstring
Java_de_joshuareibert_dontslamyourhead_MainActivity_stringFromJNI(JNIEnv* env,
                                                 jobject thiz) {
    return env->NewStringUTF(helloFromLsdSlam().c_str());
}
}
