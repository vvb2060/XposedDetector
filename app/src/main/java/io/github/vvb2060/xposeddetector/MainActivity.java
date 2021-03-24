package io.github.vvb2060.xposeddetector;

import android.app.Activity;
import android.os.Bundle;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class MainActivity extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        var layout = new RelativeLayout(this);
        var textView = new TextView(this);
        switch (getXposedStat()) {
            case 0:
                textView.setText(R.string.no_xposed);
                break;
            case 1:
                textView.setText(R.string.found_xposed);
                break;
            case 2:
                textView.setText(R.string.antied_xposed);
                break;
        }
        var params = new RelativeLayout.LayoutParams(
                RelativeLayout.LayoutParams.WRAP_CONTENT,
                RelativeLayout.LayoutParams.WRAP_CONTENT);
        params.addRule(RelativeLayout.CENTER_HORIZONTAL);
        params.addRule(RelativeLayout.CENTER_VERTICAL);
        layout.addView(textView, params);
        setContentView(layout);
    }

    private native int getXposedStat();
}
