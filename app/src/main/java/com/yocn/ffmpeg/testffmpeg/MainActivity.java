package com.yocn.ffmpeg.testffmpeg;

import android.app.Activity;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.yocn.ffmpeg.ffmpeg.LogUtil;
import com.yocn.ffmpeg.ffmpeg.OnProgressInterface;
import com.yocn.ffmpeg.ffmpeg.testFFMpeg;

import java.io.File;
import java.util.ArrayList;

public class MainActivity extends Activity implements View.OnClickListener {
    TextView mShowTv;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initView();
    }

    public void initView() {
        mShowTv = findViewById(R.id.sample_text);
        mShowTv.setText(testFFMpeg.getVersion());
        Button bt_do = findViewById(R.id.tv_do);
        bt_do.setOnClickListener(this);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    @Override
    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.tv_do:
                String targetPath = FileUtils.copyAssetsFile2Phone(this, "video.mp4");
                String targetGifPath = new File(targetPath).getParentFile().getAbsolutePath() + "/target.gif";
                LogUtil.d("sourceFilePath->" + targetPath + " \ngifPath->" + targetGifPath);
                String cmd = "ffmpeg -i " + targetPath + " -vframes 30 -y -f gif " + targetGifPath;
                ArrayList<String> cmds = new ArrayList<>();

                String[] ss = cmd.split(" ");
                for (String s : ss) {
                    cmds.add(s);
                }

                
                testFFMpeg.setProgressInterface(new OnProgressInterface() {
                    @Override
                    public void onProgress(String id, int progress) {
                        LogUtil.d("yocn currentThread->" + Thread.currentThread().getName());
                        MainActivity.this.runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                mShowTv.setText("Done!");
                            }
                        });
                    }
                });

//        int re = testFFMpeg.execCmd(cmds.toArray(new String[0]));
//        int re = testFFMpeg.execCmdWithCallback1(cmds.toArray(new String[0]));
                int re = testFFMpeg.execCmdWithCallbackInBgThread(cmds.toArray(new String[0]));

                break;
            default:
                break;
        }
    }
}
