package com.wwj.jni;

import android.util.Log;

public class Animal {

    protected String name;

    public Animal(String name) {
        this.name = name;
        Log.e("hello","---Animal 构造 方法");
    }

    public String getName() {
        Log.e("hello","---Animal getName 方法");
        return name;
    }

    public void run(){
        Log.e("hello","---Animal run 方法");
    }
}
