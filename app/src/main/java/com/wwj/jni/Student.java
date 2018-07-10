package com.wwj.jni;

public class Student {

    public int []stuScore=new int[]{ 80,95,60,50,85};


    public native int sum(int stuScore[]); //370
    public native float average(float stuScore[]); //74

    public native float sum2(float stuScore[]);

}
