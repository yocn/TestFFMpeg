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

JNIEXPORT jint JNICALL
Java_com_yocn_ffmpeg_ffmpeg_testFFMpeg_execCmdWithCallback1(JNIEnv *env, jclass clazz,
                                                            jobjectArray commands) {
    /**
     * 使用class获取onProgress方法 第三个参数是方法名称，第四个参数是描述符
     * 这里需要注意
     * 1、关于第二个参数clazz指当前的class，如果是非静态方法传入的是jobject可以使用
     * jcalss jSdkClass =(*env)->GetObjectClass(env,jobject);
     * 获取到jobject的class信息，一般来说静态方法传入jclass，非静态方法传入jobject
     * 2、关于第四个参数描述符：如果是abc.java方法，可以
     * 2.1、先用javac abc.java编译得到abc.class
     * 2.2、再用javap -s abc得到此类的描述符信息
     */
    jmethodID onProgressMethod = (*env)->GetMethodID(env, clazz, "onProgress",
                                                     "(Ljava/lang/String;JJ)I");
    //获取构造方法，()V 表示返回值是void
    jmethodID initId = (*env)->GetMethodID(env, clazz, "<init>", "()V");
    //下面调用onProgress方法需要一个对象调用，所以这里new一个Object出来
    jobject testFFMpegJObject = (*env)->NewObject(env, clazz, initId);
    //这里注意调用需要的参数是JString，需要jstring而不是C里面的string
    jstring s = (*env)->NewStringUTF(env, "TAG");

    int argc = (*env)->GetArrayLength(env, commands);
    char *argv[argc];
    int i;
    for (i = 0; i < argc; i++) {
        jstring js = (jstring) (*env)->GetObjectArrayElement(env, commands, i);
        argv[i] = (char *) (*env)->GetStringUTFChars(env, js, 0);
    }
    av_log_set_callback(ffp_log_callback_report);
    int ret = ffmpeg_exec(argc, argv);

    jint callRet = (*env)->CallIntMethod(env, testFFMpegJObject, onProgressMethod, s, 1, 1);
    return ret;
}


JavaVM *g_VM;
jobject g_obj;
int argc;

void exeffMpegCMD(void *p) {
    JNIEnv *env;
    int mNeedDetach = JNI_FALSE;

    int getEnvStat = (*g_VM)->GetEnv(g_VM, (void **) &env, JNI_VERSION_1_6);
    if (getEnvStat == JNI_EDETACHED) {
        //如果没有， 主动附加到jvm环境中，获取到env
        if ((*g_VM)->AttachCurrentThread(g_VM, &env, NULL) != 0) {
            return;
        }
        mNeedDetach = JNI_TRUE;
    }

    //通过全局变量g_obj 获取到要回调的类
    jclass clazz = (*env)->GetObjectClass(env, g_obj);

    jmethodID onProgressMethod = (*env)->GetMethodID(env, clazz, "onProgress",
                                                     "(Ljava/lang/String;JJ)I");
    //获取构造方法，()V 表示返回值是void
    jmethodID initId = (*env)->GetMethodID(env, clazz, "<init>", "()V");
    //下面调用onProgress方法需要一个对象调用，所以这里new一个Object出来
    jobject testFFMpegJObject = (*env)->NewObject(env, clazz, initId);
    //这里注意调用需要的参数是JString，需要jstring而不是C里面的string
    jstring s = (*env)->NewStringUTF(env, "TAG");
    jint callRet = (*env)->CallIntMethod(env, testFFMpegJObject, onProgressMethod, s, 1, 1);

    av_log_set_callback(ffp_log_callback_report);
//    int ret = ffmpeg_exec(argc, argv);

    //释放当前线程
    if (mNeedDetach) {
        (*g_VM)->DetachCurrentThread(g_VM);
    }
    env = NULL;
}

jobjectArray g_commands;

JNIEXPORT jint JNICALL
Java_com_yocn_ffmpeg_ffmpeg_testFFMpeg_execCmdWithCallbackInBgThread(JNIEnv *env, jclass clazz,
                                                                     jobjectArray commands) {


    int argc = (*env)->GetArrayLength(env, commands);
    LOGE("aaaaaaaa %i", argc);
//    jclass cls = (*env)->FindClass(env, "java/lang/Object");
    jobject obj = (*env)->GetObjectArrayElement(env, commands, 1);
    jclass clas = (*env)->GetObjectClass(env, obj);

    g_commands = (jobjectArray) (*env)->NewObjectArray(env, argc, clas, NULL);

//    g_commands = commands;
    char *argv[argc];
    int i;
    for (i = 0; i < argc; i++) {
        jstring js = (jstring) (*env)->GetObjectArrayElement(env, commands, i);
        argv[i] = (char *) (*env)->GetStringUTFChars(env, js, 0);
        LOGE("%c", argv[i]);
    }

    /**
     * 使用class获取onProgress方法 第三个参数是方法名称，第四个参数是描述符
     * 这里需要注意
     * 1、关于第二个参数clazz指当前的class，如果是非静态方法传入的是jobject可以使用
     * jcalss jSdkClass =(*env)->GetObjectClass(env,jobject);
     * 获取到jobject的class信息，一般来说静态方法传入jclass，非静态方法传入jobject
     * 2、关于第四个参数描述符：如果是abc.java方法，可以
     * 2.1、先用javac abc.java编译得到abc.class
     * 2.2、再用javap -s abc得到此类的描述符信息
     */
    //获取构造方法，()V 表示返回值是void
    jmethodID initId = (*env)->GetMethodID(env, clazz, "<init>", "()V");
    //下面调用onProgress方法需要一个对象调用，所以这里new一个Object出来
    jobject testFFMpegJObject = (*env)->NewObject(env, clazz, initId);

    (*env)->GetJavaVM(env, &g_VM);
    g_obj = (*env)->NewGlobalRef(env, testFFMpegJObject);

    pthread_t thread;
    pthread_create(thread, NULL, exeffMpegCMD, NULL);

    return 1;
}



