#include <jni.h>
#include <android/log.h>
#include <math.h>

#define LOGTAG "hello"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOGTAG,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOGTAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOGTAG,__VA_ARGS__)

jint Java_com_wwj_jni_MainActivity_add(JNIEnv *env, jobject instance, jint a, jint b) {

//    int __android_log_print(int prio, const char* tag, const char* fmt, ...)
    char *str = "hello log";
//    __android_log_print(ANDROID_LOG_INFO,LOGTAG,"a=%d",a);
//    __android_log_print(ANDROID_LOG_WARN,LOGTAG,"str=%s",str);
//    __android_log_print(ANDROID_LOG_ERROR,LOGTAG,"b=%d",b);
//    __android_log_print(ANDROID_LOG_WARN,LOGTAG,"a+b=%d",a+b);
    LOGI("a=%d", a);
    LOGW("my str=%s", str);
    LOGE("b=%d", b);
    LOGW("a+b=%d", a + b);
    return a + b;
}

jshort Java_com_wwj_jni_MainActivity_sub(JNIEnv *env, jobject instance, jshort a, jshort b) {
    return a - b;
}

jdouble Java_com_wwj_jni_MainActivity_multi(JNIEnv *env, jobject instance, jdouble a, jdouble b) {
    return a * b;
}

jlong Java_com_wwj_jni_MainActivity_divi(JNIEnv *env, jobject instance, jlong a, jlong b) {
    return a / b;
}

jchar Java_com_wwj_jni_MainActivity_getChar(JNIEnv *env, jobject instance, jchar a) {
    //A
    return a = a + 3; //D
}

jbyte Java_com_wwj_jni_MainActivity_sqrt(JNIEnv *env, jobject instance, jbyte a) {
    return sqrt(a);
}

jfloat Java_com_wwj_jni_MainActivity_power(JNIEnv *env, jobject instance, jfloat num, jfloat b) {
    jfloat temp=num;
    for (int i = 1; i < b; i++) {
        num *= temp;
    }
    return num;

}

jboolean Java_com_wwj_jni_MainActivity_isTrue(JNIEnv *env, jobject instance, jboolean b) {
    if(b){
        return 1;
    }else{
        return 0;
    }
}