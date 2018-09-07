package com.yocn.ffmpeg.testffmpeg;

import android.app.Activity;
import android.content.Context;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

/**
 * @Author yocn
 * @Date 2018/9/7 下午4:46
 * @ClassName FileUtils
 */
public class FileUtils {

    public static String copyAssetsFile2Phone(Context context, String fileName) {
        File rootFile = context.getExternalFilesDir("");
        String rootPath = "";
        if (rootFile != null) {
            rootPath = rootFile.getAbsolutePath();
        } else {
            rootPath = context.getFilesDir().getAbsolutePath();
        }
        String targetPath = rootPath + File.separator + fileName;

        try {
            InputStream inputStream = context.getAssets().open(fileName);
            //getFilesDir() 获得当前APP的安装路径 /data/data/包名/files 目录
            File file = new File(targetPath);
            if (!file.exists() || file.length() == 0) {
                FileOutputStream fos = new FileOutputStream(file);//如果文件不存在，FileOutputStream会自动创建文件
                int len = -1;
                byte[] buffer = new byte[1024];
                while ((len = inputStream.read(buffer)) != -1) {
                    fos.write(buffer, 0, len);
                }
                fos.flush();//刷新缓存区
                inputStream.close();
                fos.close();
//                showToast(activity, "模型文件复制完毕");
            } else {
//                showToast(activity, "模型文件已存在，无需复制");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        return targetPath;
    }
}
