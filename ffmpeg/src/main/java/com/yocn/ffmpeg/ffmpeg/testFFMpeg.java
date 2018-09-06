package com.yocn.ffmpeg.ffmpeg;

/**
 * @Author yocn
 * @Date 2018/8/8 下午12:05
 * @ClassName testFFMpeg
 */
public class testFFMpeg {
    static {
        System.loadLibrary("ffmpeg");
        System.loadLibrary("helloffmpeg");
    }

    public static native String getVersion();

}
