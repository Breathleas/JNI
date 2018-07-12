package com.wwj.jni;

import android.util.Log;

public class LocalRegister {

    /**
     * @param len 复制的字符串数量
     * @param str 要传递的字符串
     * @return
     */
    public native String[] getString(int len, String str);

    public void printStr() {
        String[] strArr = getString(10000, "I love you %d year");
        if(null!=strArr){
            for (String str : strArr) {
                Log.e("hello","--------"+ str);
            }
        }
    }

}
