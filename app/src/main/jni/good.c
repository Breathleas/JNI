#include <jni.h>
#include <android/log.h>

#define LOGTAG "hello"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOGTAG,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOGTAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOGTAG,__VA_ARGS__)

jint Java_com_wwj_jni_MainActivity_add(JNIEnv *env, jobject instance, jint a, jint b) {

//    int __android_log_print(int prio, const char* tag, const char* fmt, ...)
    char *str="hello log";
//    __android_log_print(ANDROID_LOG_INFO,LOGTAG,"a=%d",a);
//    __android_log_print(ANDROID_LOG_WARN,LOGTAG,"str=%s",str);
//    __android_log_print(ANDROID_LOG_ERROR,LOGTAG,"b=%d",b);
//    __android_log_print(ANDROID_LOG_WARN,LOGTAG,"a+b=%d",a+b);
    LOGI("a=%d",a);
    LOGW("my str=%s",str);
    LOGE("b=%d",b);
    LOGW("a+b=%d",a+b);
    return a+b;
}