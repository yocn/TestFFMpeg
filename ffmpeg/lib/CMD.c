//
// Created by 赵英坤 on 2018/9/7.
//

#include <jni.h>
#include <android/log.h>
#include <unistd.h>
//#include "ffmpeg.h"
#include "../ffmpegbin/ffmpeg.h"
#include "android_log.h"

#define LOG_TAG "libffmpeg"

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

    av_log_set_callback(ffp_log_callback_report);
    int ret = ffmpeg_exec(argc, argv);
    return ret;
}
