# Automatically generated by configure - do not modify!
shared=no
build_suffix=
prefix=/Users/yocn/AndroidStudioProjects/TestFFMpeg/ffmpeg/ffmpeg-3.4.1/../lib/arm64-v8a
libdir=${prefix}/lib
incdir=${prefix}/include
rpath=
source_path=.
LIBPREF=lib
LIBSUF=.a

extralibs_avutil=" -lm"
extralibs_avcodec="-lx264 -lfdk-aac -lm  -lz -pthread -pthread "
extralibs_avformat="-lx264 -lfdk-aac -lm  -lz -pthread -pthread "
extralibs_avdevice="-lx264 -lfdk-aac -lm  -lz -pthread -pthread "
extralibs_avfilter="-lx264 -lfdk-aac -lm  -lz -pthread -pthread "
extralibs_avresample="-lm"
extralibs_postproc=""
extralibs_swscale="-lm"
extralibs_swresample="-lm "
avcodec_deps="avutil"
avdevice_deps="avformat avcodec avutil"
avfilter_deps="avresample swscale swresample avformat avcodec avutil"
avformat_deps="avcodec avutil"
avresample_deps="avutil"
avutil_deps=""
postproc_deps="avutil"
swresample_deps="avutil"
swscale_deps="avutil"
