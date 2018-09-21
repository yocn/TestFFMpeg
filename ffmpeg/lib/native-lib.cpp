#ifdef __cplusplus
#define __STDC_CONSTANT_MACROS
#ifdef _STDINT_H
#undef _STDINT_H
#endif
extern "C" {
#include <stdint.h>
//#include <libavcodec/avcodec.h>
//#include <libavformat/avformat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
}
#endif

#include <jni.h>
#include <string>
#include <rapidjson/document.h>
#include <CMD.h>
#include <android/log.h>
#include <vector>

#define LOG_TAG "libbitmaputils"
#define LOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

using namespace rapidjson;
using namespace std;

void testJson() {
    vector<string> filenames;
    Document document;
    document.Parse(json);
    assert(document.IsArray());
    Value &root = document[0];
    Value &layersArray = root["layers"];
    if (layersArray.IsArray()) {
        for (size_t i = 0; i < layersArray.Size(); i++) {
            Value &layer = layersArray[i];
            if (layer.HasMember("transform")) {
                //含有transform key
                Value &transform = layer["transform"];
                if (transform.HasMember("filename")) {
                    string filename = transform["filename"].GetString();
                    filenames.push_back(filename);
                    LOGE("filename-> %s", filename.c_str());
                }
            }
        }
    }
    long size = filenames.size();
}

void testMask() {
    vector<string> masknames;
    Document document;
    document.Parse(mask);
    Value &masks = document["masks"];
    assert(masks.IsArray());
    for (size_t i = 0; i < masks.Size(); i++) {
        Value &mask = masks[i];
        if (mask.HasMember("filename")) {
            string filename = mask["filename"].GetString();
            masknames.push_back(filename);
            LOGE("filename-> %s", filename.c_str());
        }
    }
}

void testString() {
    string filepath = "/storage/emulated/0/Android/data/com.qutui360.app/files/res/tpls/2DF77553D9B26745F6452F7F04FCA2F5/animation.zip";
    string path;
    string filename;
    int pathPosition = 0;
    string str_pathfilename(filepath);
    pathPosition = str_pathfilename.find_last_of('/');
    pathPosition++;   //add 1,
    path.assign(str_pathfilename.c_str(), pathPosition);
    LOGE("filePath-> %s", path.c_str());
}

extern "C" JNIEXPORT jstring

JNICALL
Java_com_yocn_ffmpeg_ffmpeg_testFFMpeg_getVersion(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    char str[25];
    testJson();
    testMask();
    testString();
//    sprintf(str, "%d", avcodec_version());
    return env->NewStringUTF(hello.c_str());
}
