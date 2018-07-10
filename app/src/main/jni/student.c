#include <jni.h>
#include <android/log.h>
#include <stdlib.h>


#define LOGTAG "hello"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOGTAG,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOGTAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOGTAG,__VA_ARGS__)


JNIEXPORT jint JNICALL
Java_com_wwj_jni_Student_sum(JNIEnv *env, jobject instance, jintArray stuScore_) {

    //JNI_FALSE 不拷贝数组中的内存到缓冲区
    //JNI_TRUE  拷贝数组中的内存到缓冲
    //*stuScore 指针指向int类型数组
    //当GC扫描到stuScore_这个对象，会给这个对象加一把锁,本地方法会出阻塞状态
    jint *stuScore = (*env)->GetIntArrayElements(env, stuScore_, JNI_FALSE);

    int len = (*env)->GetArrayLength(env, stuScore_);

    int sum = 0;
    for (int i = 0; i < len; i++) {
//        sum +=stuScore[i];
        sum += *(stuScore + i);
        LOGW("stu[%d]=%d", i, *(stuScore + i));
    }
    //释放 stuScore 指针指向的缓冲区
    (*env)->ReleaseIntArrayElements(env, stuScore_, stuScore, 0);
    return sum;
}

// 这种写法传递数组的元素内容少的时候效率非常高
JNIEXPORT jfloat JNICALL
Java_com_wwj_jni_Student_average(JNIEnv *env, jobject instance, jfloatArray stuScore_) {

    int len = (*env)->GetArrayLength(env, stuScore_);

//    void* malloc(size_t __byte_count)
    float *stuScoreTemp = (float *) malloc(sizeof(jfloat) * len);

    //给学生数组赋值
    (*env)->GetFloatArrayRegion(env, stuScore_, 0, len, stuScoreTemp);

    float sum, average;
    for (int i = 0; i < len; i++) {
//        sum +=stuScore[i];
        sum += *(stuScoreTemp + i);
        LOGW("stu[%d]=%f", i, *(stuScoreTemp + i));
    }

    average = sum / len;
    return average;
}

JNIEXPORT jfloat JNICALL
Java_com_wwj_jni_Student_sum2(JNIEnv *env, jobject instance, jfloatArray stuScore_) {
//    void*       (*GetPrimitiveArrayCritical)(JNIEnv*, jarray, jboolean*);
    //指针指向原始数组,JNI_FALSE 不拷贝数组到缓冲区
    //JNI_TRUE 拷贝数组到缓冲区
    //调用这个函数时，会暂停GC线程,不能够调用 其它线程的wait或者notity
//    在 Get/ReleasePrimitiveArrayCritical 这两个函数期间不能调用任何会让线程阻塞或等待 JVM 中其它线程的本地函数或JNI函数
    jfloat *stuScore = (*env)->GetPrimitiveArrayCritical(env,stuScore_,JNI_FALSE);
    int len = (*env)->GetArrayLength(env, stuScore_);

    float sum;
    for (int i = 0; i < len; i++) {
//        sum +=stuScore[i];
        sum += *(stuScore + i);
        LOGW("stu2[%d]=%f", i, *(stuScore + i));
    }
//    void        (*ReleasePrimitiveArrayCritical)(JNIEnv*, jarray, void*, jint);
    (*env)->ReleasePrimitiveArrayCritical(env,stuScore_,stuScore,0);

    return sum;

}



