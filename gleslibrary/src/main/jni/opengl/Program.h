//
// Created by niu on 2023/11/6.
//

#ifndef ANDROID_PROGRAM_H
#define ANDROID_PROGRAM_H
#if defined(ANDROID)
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "Shader.h"

#else
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#endif

class Program{

public:
    Program();
    ~Program();

public:
    bool initialize();
    virtual void updateVertexCoords(const float *vertexCoords);
    virtual void updateTextureCoords(const float *textureCoords);
    virtual void updateMatrix(const float *matrix);
    // @param: percent range [0, 100]
    virtual void adjust(int percent) {}

protected:
    virtual bool onInit();
    virtual const char *getVertextShaderSource() const;
    virtual const char  *getFragmentShaderSource() const;

private:
    unsigned int loadProgram();
    static void printErrorInfo(const Shader& shader, const Shader& shader1, GLuint program);

protected:
    unsigned int mProgramId;
    int mVertexCoordIndex;
    int mTextureCoordIndex;
    int mMetrixIndex;
    int mTexIndex;
};
#endif //ANDROID_PROGRAM_H
