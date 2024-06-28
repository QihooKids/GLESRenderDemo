package com.example.nativelib

import android.graphics.Bitmap

class NativeLib {

    /**
     * A native method that is implemented by the 'nativelib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    external fun resize(imgData: Bitmap, outBitmap: Bitmap, width:Int, height:Int, scale:Float)

    companion object {
        // Used to load the 'nativelib' library on application startup.
        init {
            System.loadLibrary("nativelib")
        }
    }
}