package com.yocn.ffmpeg.ffmpeg;

/**
 * @Author yocn
 * @Date 2018/8/8 下午12:05
 * @ClassName testFFMpeg
 */
public class testFFMpeg {

    static OnProgressInterface mProgressInterface;

    static {
        System.loadLibrary("ffmpeg");
        System.loadLibrary("helloffmpeg");
    }

    public testFFMpeg() {
    }

    //单例
    private static class Hodler {
        static testFFMpeg instance = new testFFMpeg();
    }

    public static testFFMpeg getInstance() {
        return Hodler.instance;
    }

    public static void setProgressInterface(OnProgressInterface mProgressInterface) {
        testFFMpeg.mProgressInterface = mProgressInterface;
    }

    public int onProgress(String TAG, long total, long current) {
        LogUtil.d(TAG + " ------------- " + total + " ----------------- " + current);
        testFFMpeg.mProgressInterface.onProgress("gif", 100);
        return 0;
    }

    //获取ffmpeg版本号
    public static native String getVersion();

    //执行ffmpeg命令行
    public static native int execCmd(String[] cmd);

    //执行命令行 回调
    public static native int execCmdWithCallback1(String[] cmd);

    //执行命令行 回调
    public static native int execCmdWithCallbackInBgThread(String[] cmd);


}
