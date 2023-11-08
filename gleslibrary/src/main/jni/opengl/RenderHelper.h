//
// Created by niu on 2023/11/7.
//

#ifndef ANDROID_RENDERHELPER_H
#define ANDROID_RENDERHELPER_H
#ifdef __cplusplus
extern "C"
{
#endif
 long createRender(unsigned int width, unsigned int height);
 void release(long handle);
 void render(long handle, unsigned char *data, int width, int height);
#ifdef __cplusplus
}
#endif
#endif //ANDROID_RENDERHELPER_H
