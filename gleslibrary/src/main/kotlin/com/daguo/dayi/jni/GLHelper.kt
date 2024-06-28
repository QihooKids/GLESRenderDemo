package com.daguo.dayi.jni

import android.graphics.SurfaceTexture
import android.opengl.GLUtils
import javax.microedition.khronos.egl.EGL10
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.egl.EGLContext
import javax.microedition.khronos.opengles.GL

class GLHelper {
    private lateinit var mEgl: EGL10
    private var mGL: GL? = null
    private var mEglDisplay = EGL10.EGL_NO_DISPLAY
    private var mEglContext = EGL10.EGL_NO_CONTEXT
    private var mEglSurface = EGL10.EGL_NO_SURFACE

    fun initGL(surfaceTexture: SurfaceTexture) {
        mEgl = EGLContext.getEGL() as EGL10
        mEglDisplay = mEgl.eglGetDisplay(EGL10.EGL_DEFAULT_DISPLAY)
        if (mEglDisplay === EGL10.EGL_NO_DISPLAY) {
            val error = mEgl.eglGetError()
            throw RuntimeException("eglGetDisplay failed : ${GLUtils.getEGLErrorString(error)}")
        }
        val version = IntArray(2)
        if (!mEgl.eglInitialize(mEglDisplay, version)) {
            val error = mEgl.eglGetError()
            throw RuntimeException("eglInitialize failed : ${GLUtils.getEGLErrorString(error)}")
        }
        val configAttribs = intArrayOf(
            EGL10.EGL_BUFFER_SIZE, 32,
            EGL10.EGL_ALPHA_SIZE, 8,
            EGL10.EGL_BLUE_SIZE, 8,
            EGL10.EGL_GREEN_SIZE, 8,
            EGL10.EGL_RED_SIZE, 8,
            EGL10.EGL_DEPTH_SIZE, 24,
            EGL10.EGL_STENCIL_SIZE, 8,
            EGL10.EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL10.EGL_SURFACE_TYPE, EGL10.EGL_WINDOW_BIT,
            EGL10.EGL_NONE
        )
        val numConfigs = IntArray(1)
        val configs = arrayOfNulls<EGLConfig>(1)
        if (!mEgl.eglChooseConfig(mEglDisplay, configAttribs, configs, 1, numConfigs)) {
            val error = mEgl.eglGetError()
            throw RuntimeException("eglChooseConfig failed : ${GLUtils.getEGLErrorString(error)}")
        }
        val contextAttribs = intArrayOf(
            EGL_CONTEXT_CLIENT_VERSION, 2,
            EGL10.EGL_NONE
        )
        mEglContext =
            mEgl.eglCreateContext(mEglDisplay, configs[0], EGL10.EGL_NO_CONTEXT, contextAttribs)
        mEglSurface = mEgl.eglCreateWindowSurface(mEglDisplay, configs[0], surfaceTexture, null)
        if (mEglSurface === EGL10.EGL_NO_SURFACE || mEglContext === EGL10.EGL_NO_CONTEXT) {
            val error = mEgl.eglGetError()
            if (error == EGL10.EGL_BAD_NATIVE_WINDOW) {
                throw RuntimeException("eglCreateWindowSurface returned  EGL_BAD_NATIVE_WINDOW. ")
            }
            throw RuntimeException(
                "eglCreateWindowSurface failed : ${GLUtils.getEGLErrorString(error)}"
            )
        }
        if (!mEgl.eglMakeCurrent(mEglDisplay, mEglSurface, mEglSurface, mEglContext)) {
            val error = mEgl.eglGetError()
            throw RuntimeException("eglMakeCurrent failed : ${GLUtils.getEGLErrorString(error)}")
        }
        mGL = mEglContext.gl
    }

    fun destroyGL() {
        mEgl.apply {
            eglMakeCurrent(mEglDisplay, EGL10.EGL_NO_SURFACE, EGL10.EGL_NO_SURFACE, EGL10.EGL_NO_CONTEXT);
            eglDestroyContext(mEglDisplay, mEglContext)
            eglDestroySurface(mEglDisplay, mEglSurface)
        }
        mEglContext = EGL10.EGL_NO_CONTEXT
        mEglSurface = EGL10.EGL_NO_SURFACE
    }

    fun swapBuffers(): Boolean {
        return mEgl.eglSwapBuffers(mEglDisplay, mEglSurface)
    }

    companion object {
        private const val EGL_CONTEXT_CLIENT_VERSION = 0x3098
        private const val EGL_OPENGL_ES2_BIT = 4
    }
}