#include <jni.h>
#include "RenderHelper.h"
#include <android/log.h>
//
// Created by niu on 2023/11/7.
//
#define LOG_TAG "Render_JNI"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

jint textureId(long i);

#ifdef __cplusplus
extern "C"
{
#endif
JNIEXPORT jlong JNICALL
Java_com_daguo_dayi_jni_GLESRender_init(JNIEnv *env, jobject thiz, jint width, jint height) {
    LOGE("Jni init create render...");
    return createRender(width, height);
}

JNIEXPORT void JNICALL
Java_com_daguo_dayi_jni_GLESRender_render(JNIEnv *env, jobject thiz, jlong handle,
                                          jbyteArray byte_array, jint width, jint height) {
    jbyte *byteArr = (*env)->GetByteArrayElements(env, byte_array, NULL);
    render((long)handle, (unsigned char *)byteArr, width, height);
    (*env)->ReleaseByteArrayElements(env, byte_array, byteArr, 0);
}

JNIEXPORT void JNICALL
Java_com_daguo_dayi_jni_GLESRender_release(JNIEnv *env, jobject thiz, jlong handle) {
    release((long)handle);
}

jint JNICALL
Java_com_daguo_dayi_jni_GLESRender_textureId(JNIEnv *env, jobject thiz, jlong handle) {
    return textureId((long)handle);
}

#ifdef __cplusplus
}
#endif








