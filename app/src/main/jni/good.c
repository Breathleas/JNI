#include <jni.h>
#include <android/log.h>
#include <math.h>
#include <string.h>

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

/**
 * @param env
 * @param instance
 * 当是非静态函数的时候，jobject是对象实例
 * 当时静态函数的时候，jobect是类实例
 * @param a
 * @param b
 * @return
 */
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
    LOGW("divi------a=%ld,b=%ld,res=%ld", a, b, res);
    return res;
}

/**
 *
 * @param env
 * @param instance
 * 当是非静态函数的时候,jobject 是对象实例
 * 当是静态函数的时候，jobejct 是类实例
 * @param a
 * @return
 */
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

//C/C++ 代码是UTF-8
JNIEXPORT jstring JNICALL
Java_com_wwj_jni_MainActivity_sayHello(JNIEnv *env, jobject instance, jstring str_) {
    //函数内部会分配内存空间
    //JNI_FALSE 不拷贝jstring对象的字符序列
    //JNI_TRUE 拷贝jstring独享的字符串序列
    const char *str = (*env)->GetStringUTFChars(env, str_, JNI_FALSE);

    LOGE("----c str=%s", str);

    char buff[100] = {"I am from C! \t"};
    strcat(buff, str);
    strcat(buff, "\n");
    LOGE("----c buff=%s\n", buff);

    //释放函数内部的内存空间
    (*env)->ReleaseStringUTFChars(env, str_, str);

    //把UTF-8编码转换为Unicode编码
    return (*env)->NewStringUTF(env, buff);
}

JNIEXPORT jstring JNICALL
Java_com_wwj_jni_MainActivity_subStr(JNIEnv *env, jobject instance, jstring str_) {
    int len = (*env)->GetStringUTFLength(env, str_);

//    void        (*GetStringUTFRegion)(JNIEnv*, jstring, jsize, jsize, char*);
    char buff[len];
    //内部没有分配内存空间，所以不需要释放
    (*env)->GetStringUTFRegion(env, str_, 5, len - 5, buff);//获取字符串的一部分内容
    LOGE("-----c str=%s\n",buff);
    strcat(buff,"\r\n");

    //把UTF-8编码转换为Unicode编码
    return (*env)->NewStringUTF(env, buff);
}

