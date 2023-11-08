//
// Created by niu on 2023/11/3.
//
#ifndef ANDROID_TEXTURES_H
#define ANDROID_TEXTURES_H

#if defined(ANDROID)
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#else
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#endif

class Textures{
public:
    Textures(GLsizei num, GLuint *textures);
    ~Textures();
public:
    void init();
    void release();
    void loadTexture(unsigned int index, unsigned char* data,  GLint format, GLsizei width, GLsizei height);

private:
    GLuint *mTextures;
    GLsizei mNum;
    unsigned mWidth;
    unsigned mHeight;

    static void bindTexture(GLuint i);

    bool checkSizeChanged(unsigned int width, unsigned int height);
};

#endif //ANDROID_TEXTURES_H
