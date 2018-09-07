package com.yocn.ffmpeg.testffmpeg;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import com.yocn.ffmpeg.ffmpeg.testFFMpeg;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(testFFMpeg.getVersion());

        String cmd = "ffmpeg -version";
        ArrayList<String> cmds = new ArrayList<>();

        String[] ss = cmd.split(" ");
        for (String s : ss) {
            cmds.add(s);
        }

        int re = testFFMpeg.execCmd(cmds.toArray(new String[0]));

        tv.setText(re + "");
//        testFFMpeg.test();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}
