package io.github.vvb2060.xposeddetector;

import android.app.Application;

public class App extends Application {
    static {
        System.loadLibrary("vvb2060");
    }
}
