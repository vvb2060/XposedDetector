package io.github.vvb2060.xposeddetector;

import android.app.Activity;
import android.os.Bundle;

import io.github.vvb2060.xposeddetector.databinding.ActivityMainBinding;

public class MainActivity extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        ActivityMainBinding binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        switch (getXposedStat()) {
            case 0:
                binding.textView.setText(R.string.no_xposed);
                break;
            case 1:
                binding.textView.setText(R.string.found_xposed);
                break;
            case 2:
                binding.textView.setText(R.string.antied_xposed);
                break;
        }
    }

    native int getXposedStat();
}
