package com.daguo.dayi.jni

class GLESRender {
    init {
        System.loadLibrary("gles_render")
    }

    external fun init(width:Int, height:Int):Long
    external fun render(handle:Long, byteArray: ByteArray, width: Int, height: Int)
    external fun release(handle:Long)
}