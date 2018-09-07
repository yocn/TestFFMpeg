//
// Created by 赵英坤 on 2018/9/7.
//

#include <jni.h>
#include <android/log.h>
#include <unistd.h>
//#include "ffmpeg.h"
#include "../ffmpegbin/ffmpeg.h"

#include <android/log.h>

#define LOG_TAG "libffmpeg"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,"%s",__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,"%s",__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOG_TAG,"%s",__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,"%s",__VA_ARGS__)
#define LOG_I(format, ...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,format,__VA_ARGS__)
#define LOG_D(format, ...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,format,__VA_ARGS__)
#define LOG_W(format, ...) __android_log_print(ANDROID_LOG_WARN,LOG_TAG,format,__VA_ARGS__)


JNIEXPORT jint JNICALL
Java_com_yocn_ffmpeg_ffmpeg_testFFMpeg_execCmd(JNIEnv *env, jclass clazz,
                                               jobjectArray commands) {
    int argc = (*env)->GetArrayLength(env, commands);
    char *argv[argc];
    int i;
    for (i = 0; i < argc; i++) {
        jstring js = (jstring) (*env)->GetObjectArrayElement(env, commands, i);
        argv[i] = (char *) (*env)->GetStringUTFChars(env, js, 0);
    }

//    av_log_set_callback(log_callback_report_for_cmd);

    LOGE("yoyo0-0-0- ");
    int ret = ffmpeg_exec(argc, argv);
    LOGE("yoyo " + ret);
//    av_log_set_callback(NULL);
    return ret;
}
