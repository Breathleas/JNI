package com.wwj.jni;

import android.util.Log;

public class Person {


    /**
     * C/CPP调用JAVA的静态方法
     */
    public native void callJavaStaticMethod();

    /**
     * C/CPP调用JAVA的实例方法
     */
    public native void callJavaInstanceMethod();


    public static void setPersonInfo(String name,int age){
        Log.e("hello","------setPersonInfo----name="+name+"----age="+age);
    }

    public void setPersonMoney(float money){
        Log.e("hello","-----setPersonMoney--money="+money);
    }


}
