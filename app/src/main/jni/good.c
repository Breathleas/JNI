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
//    LOGI("a=%d", a);
//    LOGW("my str=%s", str);
//    LOGE("b=%d", b);
//    LOGW("a+b=%d", a + b);
    int res = a + b;
    LOGW("add-------a=%d,b=%d,res=%d", a, b, res);
    return res;
}

jshort Java_com_wwj_jni_MainActivity_sub(JNIEnv *env, jobject instance, jshort a, jshort b) {
    int res = a - b;
    LOGW("sub------a=%d,b=%d,res=%d", a, b, res);
    return res;
}

jdouble Java_com_wwj_jni_MainActivity_multi(JNIEnv *env, jobject instance, jdouble a, jdouble b) {
    double res = a * b;
    LOGW("multi------a=%lf,b=%lf,res=%lf", a, b, res);
    return res;
}

jlong Java_com_wwj_jni_MainActivity_divi(JNIEnv *env, jobject instance, jlong a, jlong b) {
    long res = a / b;
    LOGW("divi------a=%d,b=%d,res=%d", a, b, res);
    return res;
}

jchar Java_com_wwj_jni_MainActivity_getChar(JNIEnv *env, jobject instance, jchar a) {
    //A
    char res = a + 3;
    LOGI("getChar------a=%c,res=%c", a, res);
    return res; //D
}

jbyte Java_com_wwj_jni_MainActivity_sqrt(JNIEnv *env, jobject instance, jbyte a) {
    int csize = sizeof(char);
    int res = sqrt(a);
    LOGI("sqrt-----%d,a=%d,res=%d", csize, a, res);
    return res;
}

jfloat Java_com_wwj_jni_MainActivity_power(JNIEnv *env, jobject instance, jfloat num, jfloat b) {
    float res = num;
    for (int i = 1; i < b; i++) {
        res *= num;
    }
    LOGE("power-------num=%f,b=%f,res=%f", num, b, res);
    return res;

}

jboolean Java_com_wwj_jni_MainActivity_isTrue(JNIEnv *env, jobject instance, jboolean b) {
    LOGE("isTrue----b=%d", b);
    if (b) {
        return 1;
    } else {
        return 0;
    }
}