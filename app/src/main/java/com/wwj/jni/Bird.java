package com.wwj.jni;

import android.util.Log;

public class Bird extends Animal {

    //(参数类型)返回值类型    (Ljava/lang/String;)V
    public Bird(String name) {
        super(name);
        Log.e("hello","---Bird 构造 方法");
    }

    public String getName() {
        Log.e("hello","---Bird getName 方法");
        return name;
    }

    public void run(){
        Log.e("hello","---Bird run 方法");
    }

}
