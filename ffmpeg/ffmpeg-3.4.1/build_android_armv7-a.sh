#!/bin/bash
NDK=$ANDROID_NDK_ROOT
NDK_ROOT=$NDK
PLATFORM=$NDK/platforms/android-18/arch-arm/
PREBUILT=$NDK/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64
PROJECT_PATH=$(pwd)
PREFIX=$(pwd)/../lib/arm64-v8a

#armeabi-v7a

echo $(pwd)

echo $PREBUILT
EXTRA_CFLAGS="-fdata-sections -ffunction-sections -fstack-protector-strong -ffast-math -fstrict-aliasing -march=armv7-a -mtune=cortex-a8 -mfloat-abi=softfp -mfpu=vfpv3-d16 -D__ANDROID_API__=18 --sysroot $NDK_ROOT/sysroot -isystem $NDK_ROOT/sysroot/usr/include/arm-linux-androideabi -I$PROJECT_PATH/third/include/"

EXTRA_LDFLAGS="-Wl,--gc-sections -Wl,-z,relro -Wl,-z,now -Wl,--fix-cortex-a8 --sysroot $NDK_ROOT/platforms/android-18/arch-arm,-rpath-link=$PLATFORM/usr/lib -L$PLATFORM/usr/lib -nostdlib -lc -lm -ldl -llog -L$PROJECT_PATH/third/lib/"

ADDITIONAL_CONFIGURE_FLAG="--arch=arm --cpu=armv7-a --enable-armv5te --enable-armv6 --enable-vfp --enable-neon"

function build_one
{
./configure \
--prefix=$PREFIX \
--enable-thumb \
--enable-runtime-cpudetect \
--cross-prefix=$PREBUILT/bin/arm-linux-androideabi- \
--target-os=android \
--enable-cross-compile \
--sysroot=$PLATFORM \
--disable-debug \
--disable-shared \
--enable-static \
--enable-asm \
--enable-neon \
--enable-gpl \
--disable-encoders \
--disable-decoders \
--disable-muxers \
--disable-demuxers \
--disable-parsers \
--disable-bsfs \
--disable-protocols \
--disable-indevs \
--disable-programs \
--disable-ffmpeg \
--disable-doc \
--disable-ffmpeg \
--disable-ffplay \
--disable-ffprobe \
--disable-ffserver \
--disable-doc \
--disable-symver \
--disable-v4l2_m2m \
--disable-postproc \
--disable-filter=showcqt \
--disable-network \
--enable-avcodec \
--enable-avformat \
--enable-avutil \
--enable-swscale  \
--enable-swresample \
--enable-avresample \
--enable-avfilter \
--enable-pic \
--enable-nonfree \
--enable-small \
--enable-libx264 \
--enable-libfdk-aac \
--enable-zlib \
--enable-demuxer=mpegts \
--enable-demuxer=mov \
--enable-demuxer=flv \
--enable-demuxer=image2 \
--enable-demuxer=mp3 \
--enable-muxer=mpegts \
--enable-muxer=mp4 \
--enable-muxer=mp3 \
--enable-protocol=file \
--enable-decoder=mjpeg \
--enable-decoder=mp3 \
--enable-decoder=h264 \
--enable-decoder=libfdk_aac \
--enable-encoder=libx264 \
--enable-encoder=libfdk_aac \
--enable-parser=h264 \
--enable-parser=aac \
--enable-muxer=gif \
--enable-encoder=gif \
--enable-demuxer=rawvideo \
--enable-muxer=wav \
--enable-demuxer=wav \
--enable-demuxer=pcm_s16le \
--enable-muxer=pcm_s16le \
--enable-encoder=pcm_s16le \
--enable-decoder=pcm_s16le \
--enable-demuxer=aac \
--enable-decoder=rawvideo \
--enable-pthreads \
--enable-jni \
--enable-mediacodec \
--extra-cflags="$EXTRA_CFLAGS" \
--extra-ldflags="$EXTRA_LDFLAGS" \
$ADDITIONAL_CONFIGURE_FLAG

make clean
make
make install

echo "make install over"

$PREBUILT/bin/arm-linux-androideabi-ar d libavcodec/libavcodec.a inverse.o

$PREBUILT/bin/arm-linux-androideabi-ld \
-rpath-link=$PLATFORM/usr/lib -L$PLATFORM/usr/lib \
-L$PROJECT_PATH/third/lib  \
-soname libffmpeg.so -shared -nostdlib  -z noexecstack -Bsymbolic --whole-archive --no-undefined -o \
$PREFIX/libffmpeg.so \
libavcodec/libavcodec.a \
libavformat/libavformat.a \
libavutil/libavutil.a \
libavfilter/libavfilter.a \
libswscale/libswscale.a \
libswresample/libswresample.a \
libavresample/libavresample.a \
third/lib/libfdk-aac.a \
third/lib/libx264.a \
-lc -lm -lz -ldl -llog --dynamic-linker=/system/bin/linker \
$PREBUILT/lib/gcc/arm-linux-androideabi/4.9.x/libgcc.a
$PREBUILT/bin/arm-linux-androideabi-strip $PREFIX/libffmpeg.so

$PREBUILT/bin/arm-linux-androideabi-strip $PREFIX/libffmpeg.so
cp config.h $PREFIX/.
#cp config.log $PREFIX/.
cp third/lib/*.a  $PREFIX/lib/
}
build_one
