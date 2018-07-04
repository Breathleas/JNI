#include <jni.h>


jstring Java_com_wwj_jni_MainActivity_stringFromJNI(JNIEnv *env, jobject instance) {


    return (*env)->NewStringUTF(env, "I am form c");
}

