//
// Created by niu on 2023/11/3.
//

#ifndef ANDROID_SHADER_H
#define ANDROID_SHADER_H
#if defined(ANDROID)
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#else
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#endif

class Shader {
private:
    GLuint mShader;
    const char* mSource;
    const unsigned int mShaderType;
public:
    Shader(const char* source, const unsigned int shaderType);
    ~Shader();
public:
    unsigned int loadShader();
    void deleteShader();
    GLuint shader() const;

    void logError() const;
};

#endif //ANDROID_SHADER_H
