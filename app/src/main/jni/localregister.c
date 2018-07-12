#include <jni.h>
#include <android/log.h>
#include <string.h>
#include <stdio.h>

#define LOGTAG "hello"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOGTAG,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOGTAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOGTAG,__VA_ARGS__)


//JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved);
//JNIEXPORT void JNI_OnUnload(JavaVM* vm, void* reserved);
jclass clsGlobalWeak;

//String[] getString(int len, String str);
jobjectArray getString(JNIEnv *env, jobject instance, jint len, jstring str) {

    //字符串数组
    jobjectArray strArrObj = NULL;

    //1 获取String 类类型
    jclass clsString = (*env)->FindClass(env, "java/lang/String");
    if (NULL == clsString) {
        LOGE("---clsString 没有找到");
        return NULL;
    }
    //2 获取字符串构造函数ID
//    public String()
    jmethodID midStr = (*env)->GetMethodID(env, clsString, "<init>", "()V");

    //3 通过构造函数创建一个字符串对象
    jstring strObj = (*env)->NewObject(env, clsString, midStr);

    //4 创建字符串数组
    strArrObj = (*env)->NewObjectArray(env, len, clsString, strObj);

    //5 给字符串数组赋值
    /**
     * 设置对象数组中指定index的值
     *
     * @param env JNI接口指针
     * @param array java数组
     * @param index 索引
     * @param value 新的值
     *
     * @throws ArrayIndexOutOfBoundsException
     */
//    void (*SetObjectArrayElement)(JNIEnv *, jobjectArray, jsize, jobject);
    const char *c_str = (*env)->GetStringUTFChars(env, str, JNI_FALSE);
    char buff[50];
    for (int i = 1; i <= len; i++) {
        memset(buff, '\0', sizeof(buff));
        sprintf(buff, c_str, i);
        jstring jstr = (*env)->NewStringUTF(env, buff);
        (*env)->SetObjectArrayElement(env, strArrObj, i - 1, jstr);
        (*env)->DeleteLocalRef(env,jstr); //删除局部引用
    }

    return strArrObj;
}


//动态链接库刚加载时调用JNI_OnLoad函数
JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGE("--------JNI_OnLoad----");
//    jint GetEnv(JavaVM *vm, void **env, jint version);
    JNIEnv *env;
    if ((*vm)->GetEnv(vm, (void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        env = NULL;
        return JNI_ERR;
    }

    //1 获取类类型
    jclass clsLoalRegister = (*env)->FindClass(env, "com/wwj/jni/LocalRegister");
    if (NULL == clsLoalRegister) {
        LOGE("---clsLoalRegister 没有找到");
        return JNI_VERSION_1_6;
    }
    //把局部引用设置为全局弱引用
    clsGlobalWeak = (*env)->NewWeakGlobalRef(env, clsLoalRegister);

//    public native String[] getString(int len, String str);
    JNINativeMethod jniNativeMethod;
    jniNativeMethod.name = "getString";
    jniNativeMethod.signature = "(ILjava/lang/String;)[Ljava/lang/String;";
    jniNativeMethod.fnPtr = getString;

    /**
    * 为clazz类注册本地方法
    *
    * @param env JNI接口指针
    * @param clazz class对象
    * @param methods clazz类中的本地方法，指向方法数组
    * @param nMethods 本地方法个数
    *
    * @return 0：成功， 负数：失败
    *
    * @throws NoSuchMethodError
    */
//    jint (*RegisterNatives)(JNIEnv *, jclass, const JNINativeMethod *, jint);
    if (0 == (*env)->RegisterNatives(env, clsLoalRegister, &jniNativeMethod, 1)) {
        LOGE("----getString本地方法注册成功=====");
    }
    (*env)->DeleteLocalRef(env, clsLoalRegister);
    return JNI_VERSION_1_6;
}

//当动态链接库卸载时
JNIEXPORT void JNI_OnUnload(JavaVM *vm, void *reserved) {

    JNIEnv *env;
    if ((*vm)->GetEnv(vm, (void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        env = NULL;
        return;
    }
    if (NULL != clsGlobalWeak) {
        (*env)->UnregisterNatives(env, clsGlobalWeak);  //取消注册

        //删除全局的弱引用,如果不手动删除，会一直保存在JVM的引用表中
        (*env)->DeleteWeakGlobalRef(env, clsGlobalWeak);
    }
}

