//
// Created by niu on 2023/11/3.
//
#include "Shader.h"
#include "Logs.h"
#include <cstdlib>

Shader::Shader(const char *source, const unsigned int shaderType) :
        mShader(0),
        mShaderType(shaderType),
        mSource(source){}

unsigned int Shader::loadShader() {
    mShader = glCreateShader(mShaderType);
    if (mShader){
        glShaderSource(mShader, 1, &mSource, nullptr);
        glCompileShader(mShader);
        GLint compiled = 0;
        glGetShaderiv(mShader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            logError();
            glDeleteShader(mShader);
            mShader = 0;
        }
    }
    return mShader;
}

Shader::~Shader() {
    deleteShader();
}

void Shader::deleteShader() {
    if(mShader>0){
        glDeleteShader(mShader);
        mShader = 0;
    }
}

void Shader::logError() const {
    GLint infoLen = 0;
    glGetShaderiv(mShader, GL_INFO_LOG_LENGTH, &infoLen);
    if (infoLen > 1) {
        char *infoLog = (char *) malloc(sizeof(char) * (infoLen + 1));
        if (infoLog != nullptr) {
            infoLog[infoLen] = '\0';
            logE("Compile mShader failed:%d , %s", mShaderType, infoLog);
            free(infoLog);
        }
    }
}

GLuint Shader::shader() const {
    return mShader;
}
