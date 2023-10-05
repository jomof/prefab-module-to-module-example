#include <jni.h>
#include <string>
#include "other-lib.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = otherLibFunction();
    return env->NewStringUTF(hello.c_str());
}