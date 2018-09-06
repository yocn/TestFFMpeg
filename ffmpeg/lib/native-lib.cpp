#ifdef __cplusplus
#define __STDC_CONSTANT_MACROS
#ifdef _STDINT_H
#undef _STDINT_H
#endif
extern "C" {
#include <stdint.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
}
#endif

#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring

JNICALL
Java_com_yocn_ffmpeg_ffmpeg_testFFMpeg_getVersion(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    char str[25];
    sprintf(str, "%d", avcodec_version());
    return env->NewStringUTF(str);
}
