#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_renovation_codec2_MainActivity_stringFromJNI3(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
