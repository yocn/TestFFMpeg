package com.yocn.ffmpeg.testffmpeg;

import android.app.Activity;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.TextView;

import com.yocn.ffmpeg.ffmpeg.LogUtil;
import com.yocn.ffmpeg.ffmpeg.OnProgressInterface;
import com.yocn.ffmpeg.ffmpeg.testFFMpeg;

import java.io.File;
import java.util.ArrayList;

public class MainActivity extends Activity implements View.OnClickListener {
    TextView mShowTv;
    ProgressBar mProgressBar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initView();
        String s = testFFMpeg.getVersion();
        LogUtil.d("yocn s->" + s);
    }

    public void initView() {

        mProgressBar = findViewById(R.id.pb_progress);

        mShowTv = findViewById(R.id.sample_text);
        Button bt_do = findViewById(R.id.tv_do);
        bt_do.setOnClickListener(this);
    }

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

                mProgressBar.setVisibility(View.VISIBLE);

                testFFMpeg.setProgressInterface(new OnProgressInterface() {
                    @Override
                    public void onProgress(String id, int progress) {
                        LogUtil.d("yocn currentThread->" + Thread.currentThread().getName());
                        MainActivity.this.runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                mShowTv.setText("Done!");
                                mProgressBar.setVisibility(View.GONE);
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
