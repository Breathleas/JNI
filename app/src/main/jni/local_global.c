#include <jni.h>
#include <android/log.h>
#include <math.h>
#include <string.h>

#define LOGTAG "hello"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOGTAG,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOGTAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOGTAG,__VA_ARGS__)


//全局引用变量虚拟机不会释放，需要我们手动释放
jclass clsBirdGlobal;

JNIEXPORT void JNICALL
Java_com_wwj_jni_MainActivity_local_1global(JNIEnv *env, jobject instance) {

    //1 获取类类型
    jclass clsBird = NULL;
    if (NULL == clsBirdGlobal) {
        clsBird = (*env)->FindClass(env, "com/wwj/jni/Bird");
    }else{
        LOGE("-----------Bird 变量的全局引用不为空");
        clsBird=clsBirdGlobal;
    }

    if (NULL == clsBird) {
        LOGE("---C 没有找到Bird类");
        return;
    }
    jclass clsBirdLoacl = (*env)->NewLocalRef(env, clsBird);

    //全局引用和局部引用都会阻塞GC线程回收对象
//    jobject     (*NewGlobalRef)(JNIEnv*, jobject);
    if (NULL == clsBirdGlobal) {
        clsBirdGlobal = (*env)->NewGlobalRef(env, clsBird);
    }

    jclass   clsAnimal = (*env)->FindClass(env, "com/wwj/jni/Animal");

    //错误的写法---------------
//    static jclass clsGlobalAnimal=NULL;
//     jclass clsAnimal=NULL;
//    if(NULL==clsGlobalAnimal){
//        clsAnimal = (*env)->FindClass(env, "com/wwj/jni/Animal");
//        //这是一个错误的写法
//        clsGlobalAnimal=clsAnimal;
//    }else{
//        LOGE("------clsGlobalAnimal 不为空");
//        clsAnimal=clsGlobalAnimal;
//    }
    //错误的写法---------------


    if (NULL == clsAnimal) {
        LOGE("---C 没有找到Animal类");
        return;
    }


    //2 获取构造函数id
    jmethodID birdConstructId = (*env)->GetMethodID(env, clsBirdLoacl, "<init>",
                                                    "(Ljava/lang/String;)V");
    if (NULL == birdConstructId) {
        LOGE("---C 没有找到Bird类的构造函数");
        return;
    }


    //3 创建一个对象
//    jobject     (*NewObject)(JNIEnv*, jclass, jmethodID, ...);
    jstring name = (*env)->NewStringUTF(env, "啄木鸟");
    if (NULL == name) {
        LOGE("---C 创建小鸟名字失败");
        return;
    }
    jobject bird = (*env)->NewObject(env, clsBirdLoacl, birdConstructId, name);
    if (NULL == bird) {
        LOGE("---C 创建小鸟对象失败");
        return;
    }

    //4 获取Bird getName方法
    jmethodID getNameId = (*env)->GetMethodID(env, clsBirdGlobal, "getName",
                                              "()Ljava/lang/String;");
    if (NULL == getNameId) {
        LOGE("---C 没有获取小鸟getName方法");
        return;
    }

//  jobject     (*CallObjectMethod)(JNIEnv*, jobject, jmethodID, ...);
    //5 调用自己的bird类方法
    jstring getName = (*env)->CallObjectMethod(env, bird, getNameId);
    if (NULL != getName) {
        //    const char* (*GetStringUTFChars)(JNIEnv*, jstring, jboolean*);
        const char *c_name = (*env)->GetStringUTFChars(env, getName, JNI_FALSE);
//    void        (*ReleaseStringUTFChars)(JNIEnv*, jstring, const char*);
        LOGW("----小鸟的名字是=%s", c_name);

        if (NULL != c_name) {
            (*env)->ReleaseStringUTFChars(env, getName, c_name);
        }
    } else {
        LOGW("----没有得到小鸟的名字");
    }

    //获取Aniaml getName方法
    jmethodID getAnimalRunId = (*env)->GetMethodID(env, clsAnimal, "run", "()V");
    if (NULL == getAnimalRunId) {
        LOGE("---C 没有获取Animal getName方法");
        return;
    }
//    void        (*CallNonvirtualVoidMethod)(JNIEnv*, jobject, jclass, jmethodID, ...);
    (*env)->CallNonvirtualVoidMethod(env, bird, clsAnimal, getAnimalRunId);


    jmethodID getAnimalNameId = (*env)->GetMethodID(env, clsAnimal, "getName",
                                                    "()Ljava/lang/String;");
    if (NULL == getAnimalNameId) {
        LOGE("---C 没有获取Animal getName方法");
        return;
    }

//    jobject     (*CallNonvirtualObjectMethod)(JNIEnv*, jobject, jclass, jmethodID, ...);
    jstring animalName = (*env)->CallNonvirtualObjectMethod(env, bird, clsAnimal, getAnimalNameId);
    if (NULL != animalName) {
        //    const char* (*GetStringUTFChars)(JNIEnv*, jstring, jboolean*);
        const char *c_name = (*env)->GetStringUTFChars(env, animalName, JNI_FALSE);
//    void        (*ReleaseStringUTFChars)(JNIEnv*, jstring, const char*);
        LOGE("----动物的名字是=%s", c_name);

        if (NULL != c_name) {
            (*env)->ReleaseStringUTFChars(env, animalName, c_name);
        }
    }


    //最后，删除局部引用变量
    (*env)->DeleteLocalRef(env, clsBirdLoacl);
    (*env)->DeleteLocalRef(env, clsAnimal);
    (*env)->DeleteLocalRef(env, name);
    (*env)->DeleteLocalRef(env, bird);
    (*env)->DeleteLocalRef(env, getName);
    (*env)->DeleteLocalRef(env, animalName);

    (*env)->DeleteGlobalRef(env,clsBirdGlobal);
    clsBirdGlobal=NULL;

}

JNIEXPORT void JNICALL
Java_com_wwj_jni_MainActivity_testRefreenceCount(JNIEnv *env, jobject instance) {

    //JVM内部有一个引用表，记录着所有的变量引用，当超过最大数，造成局部表内存溢出，导致程序崩溃
//    for(int i=1;i<=512;i++){
//        jclass  personClazz=(*env)->GetObjectClass(env,instance);
//        LOGW("-----局部引用表数量====%d",i);
//    }

}