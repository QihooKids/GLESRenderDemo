package com.example.demorender

import android.content.Context
import android.graphics.BitmapFactory
import android.opengl.GLSurfaceView
import android.os.Bundle
import android.util.Log
import android.view.ViewGroup
import androidx.fragment.app.FragmentActivity
import com.daguo.dayi.jni.GLESRender
import java.nio.ByteBuffer
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class MainActivity : FragmentActivity() {
    private lateinit var myRender:MyRender
    private lateinit var gls:GLSurfaceView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        myRender = MyRender(this)
        gls = GLSurfaceView(this)
        gls.setEGLContextClientVersion(2)
        gls.setRenderer(myRender)
        setContentView(gls, ViewGroup.LayoutParams(600,600))
    }

    override fun onResume() {
        super.onResume()
        gls.onResume()
    }

    override fun onPause() {
        super.onPause()
        gls.onPause()
    }

    override fun onDestroy() {
        myRender.release()
        super.onDestroy()
    }

}
class MyRender(private val context: Context):GLSurfaceView.Renderer{
    private var mHandle: Long = 0
    private val mJni = GLESRender()
    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        Log.d("TEST", "onSurfaceCreated...")
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        Log.d("TEST", "onSurfaceChanged $width, $height...")
        mHandle = mJni.init(width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
        val bitmap = BitmapFactory.decodeResource(context.resources, R.drawable.main_launcher )
        val byteBuffer = ByteBuffer.allocate(bitmap.byteCount)
        bitmap.copyPixelsToBuffer(byteBuffer)
        byteBuffer.rewind()
        mJni.render(mHandle, byteBuffer.array(), bitmap.width, bitmap.height)
    }

    fun release() {
        mJni.release(mHandle)
    }

}