package com.wwj.jni;

public class Student {

    public int []stuScore=new int[]{ 80,95,60,50,85};

    /**
     * 学生成绩总和
     * @param stuScore
     * @return
     */
    public native int sum(int stuScore[]); //370

    /**
     * 计算学生平均成绩
     * @param stuScore
     * @return
     */
    public native float average(float stuScore[]); //74

    /**
     * 计算学生平均成绩的另一种写法
     * @param stuScore
     * @return
     */
    public native float sum2(float stuScore[]);

    /**
     * 修改学生成绩
     * @param stuScore
     * @return
     */
    public native boolean modifyStuScore(int stuScore[]);

}
