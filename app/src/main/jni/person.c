#include <jni.h>
#include <android/log.h>
#include <stdlib.h>


#define LOGTAG "hello"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOGTAG,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOGTAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOGTAG,__VA_ARGS__)

JNIEXPORT void JNICALL
Java_com_wwj_jni_Person_callJavaStaticMethod(JNIEnv *env, jobject instance) {

    //1 获取类类型，获取class对象
//    jclass      (*FindClass)(JNIEnv*, const char*);
    jclass  personClazz=(*env)->FindClass(env,"com/wwj/jni/Person");
    if(NULL==personClazz){
        LOGE("------类没有找到-----------");
        return ;
    }

    //2 获取方法ID
//    jmethodID   (*GetStaticMethodID)(JNIEnv*, jclass, const char*, const char*);
    //(函数参数)返回值    String Ljava/lang/String;   int I
    jmethodID staticMethodId=(*env)->GetStaticMethodID(env,personClazz,"setPersonInfo","(Ljava/lang/String;I)V");
    if(NULL==staticMethodId){
        LOGE("-----没有找到静态方法setPersonInfo");
        return;
    }

    jstring  *name=(*env)->NewStringUTF(env,"星际太空");
    //3 调用静态方法
//    void        (*CallStaticVoidMethod)(JNIEnv*, jclass, jmethodID, ...);
    (*env)->CallStaticVoidMethod(env,personClazz,staticMethodId,name,25);

    //删除局部变量引用,JVM内部有一个引用表，记录全局和局部变量,当超过引用表数量，造成引用表内存溢出，会
    //导致JVM崩溃
    (*env)->DeleteLocalRef(env,personClazz);
    (*env)->DeleteLocalRef(env,name);
}

JNIEXPORT void JNICALL
Java_com_wwj_jni_Person_callJavaInstanceMethod(JNIEnv *env, jobject instance) {
    //1 获取类类型，获取class对象
//    jclass      (*FindClass)(JNIEnv*, const char*);
    jclass  personClazz=(*env)->FindClass(env,"com/wwj/jni/Person");
    if(NULL==personClazz){
        LOGE("------类没有找到-----------");
        return ;
    }

    //2 获取方法ID
    jmethodID  personMonenyMethodId=(*env)->GetMethodID(env,personClazz,"setPersonMoney","(F)V");
    if(NULL==personMonenyMethodId){
        LOGE("---------没有实例方法ID");
        return;
    }

    //3先获取构函数方法ID
    jmethodID constructMethodId=(*env)->GetMethodID(env,personClazz,"<init>","()V");
    if(NULL==constructMethodId){
        LOGE("---------没有构造函数方法ID");
        return;
    }

    //4  获取默认的构造函数对象,
//    jobject     (*NewObject)(JNIEnv*, jclass, jmethodID, ...);
    jobject obj=(*env)->NewObject(env,personClazz,constructMethodId);

    if(NULL==obj){
        LOGE("---------对象创建失败");
        return;
    }


    //5 调用JAVA的实例方法
//    void        (*CallVoidMethod)(JNIEnv*, jobject, jmethodID, ...);
    float money=100;
    (*env)->CallVoidMethod(env,obj,personMonenyMethodId,money);

    //6 删除局部引用变量
    (*env)->DeleteLocalRef(env,personClazz);
    (*env)->DeleteLocalRef(env,obj);

}

JNIEXPORT jboolean JNICALL
Java_com_wwj_jni_Person_setHobbyNative(JNIEnv *env, jobject instance) {

    //1 获取类类型，获取class对象
//    jclass      (*FindClass)(JNIEnv*, const char*);
    jclass  personClazz=(*env)->GetObjectClass(env,instance);
    if(NULL==personClazz){
        LOGE("------Person类没有找到-----------");
        return JNI_FALSE;
    }

    //2 获取属性ID
//    jfieldID    (*GetFieldID)(JNIEnv*, jclass, const char*, const char*);
    jfieldID  hobbyFieldID=(*env)->GetFieldID(env,personClazz,"hobby","Ljava/lang/String;");
    if(NULL==hobbyFieldID){
        LOGE("------hobbyFieldID  null-----------");
        return JNI_FALSE;
    }

    //3 获取属性值
    jstring hobbyStr=(*env)->GetObjectField(env,instance,hobbyFieldID);
    if(NULL!=hobbyStr){
//        const char* (*GetStringUTFChars)(JNIEnv*, jstring, jboolean*);
        const  char *hobby=(*env)->GetStringUTFChars(env,hobbyStr,NULL);
        if(NULL!=hobby){
            LOGW("------hobby=%s",hobby);
            (*env)->ReleaseStringUTFChars(env,hobbyStr,hobby);
        }
    }

    //4 设置属性
//    void        (*SetObjectField)(JNIEnv*, jobject, jfieldID, jobject);
    jstring jhobby=(*env)->NewStringUTF(env,"篮球，足球，排球，羽毛球");
    (*env)->SetObjectField(env,instance,hobbyFieldID,jhobby);

    //5 删除局部引用变量
    (*env)->DeleteLocalRef(env,personClazz);
    (*env)->DeleteLocalRef(env,hobbyStr);
    (*env)->DeleteLocalRef(env,jhobby);
    return JNI_TRUE;
}

JNIEXPORT jboolean JNICALL
Java_com_wwj_jni_Person_setHappinessNative(JNIEnv *env, jobject instance) {

    //1 获取类类型，获取class对象
//    jclass      (*FindClass)(JNIEnv*, const char*);
    jclass  personClazz=(*env)->GetObjectClass(env,instance);

    if(NULL==personClazz){
        LOGE("------Person类没有找到-----------");
        return JNI_FALSE;
    }

    //2 获取属性ID
//    jfieldID    (*GetFieldID)(JNIEnv*, jclass, const char*, const char*);
    jfieldID  happinessFieldID=(*env)->GetStaticFieldID(env,personClazz,"happiness","I");
    if(NULL==happinessFieldID){
        LOGE("------happinessFieldID  null-----------");
        return JNI_FALSE;
    }

    //3 获取静态属性值
    jint happiness=(*env)->GetStaticIntField(env,personClazz,happinessFieldID);
    LOGW("----happiness=%d",happiness);

    //4 设置静态属性值
    (*env)->SetStaticIntField(env,personClazz,happinessFieldID,80);

    //5 删除局部引用变量
    (*env)->DeleteLocalRef(env,personClazz);
}

