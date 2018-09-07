LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := ffmpeg
LOCAL_SRC_FILES := $(LOCAL_PATH)/armeabi-v7a/libffmpeg.so
#下面是申明第三方头文件路径
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/armeabi-v7a/include
include $(PREBUILT_SHARED_LIBRARY)

# Program
include $(CLEAR_VARS)
LOCAL_MODULE := helloffmpeg
LOCAL_SRC_FILES := $(LOCAL_PATH)/native-lib.cpp \
  $(LOCAL_PATH)/CMD.c  \
  $(LOCAL_PATH)/../ffmpegbin/cmdutils.c  \
  $(LOCAL_PATH)/../ffmpegbin/ffmpeg_filter.c  \
  $(LOCAL_PATH)/../ffmpegbin/ffmpeg_hw.c  \
  $(LOCAL_PATH)/../ffmpegbin/ffmpeg_opt.c  \
  $(LOCAL_PATH)/../ffmpegbin/ffmpeg.c  \
  $(LOCAL_PATH)/../ffmpegbin/ffmpeg_jni.c  \

#LOCAL_C_INCLUDES += $(LOCAL_PATH)/armeabi-v7a/include
LOCAL_LDLIBS := -llog -lz
LOCAL_SHARED_LIBRARIES := ffmpeg
include $(BUILD_SHARED_LIBRARY)
