//
// Created by niu on 2023/11/3.
//
#include "Textures.h"
#include "GLHelper.h"
#include "Logs.h"

Textures::Textures(GLsizei num, GLuint *textures) :
        mNum(num),
        mTextures(textures),
        mHeight(0),
        mWidth(0){
}

void Textures::init() {
    glGenTextures(mNum, mTextures);
    GLHelper::checkGLError("init glGenTextures");
    for (int i = 0; i < mNum; ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        GLHelper::checkGLError("init glGenTextures glActiveTexture");
        logD("mTextures index%d :%d", i, mTextures[i]);
        bindTexture(mTextures[i]);
    }
}

void Textures::release() {
    if (&mTextures[0]){
        glDeleteTextures(mNum, mTextures);
        for (int i = 0; i < mNum; ++i) {
            mTextures[i] = 0;
        }
    }
}

void Textures::loadTexture(unsigned int index, unsigned char *data, GLint format, GLsizei width, GLsizei height) {
    bool changed = checkSizeChanged(width, height);
    glActiveTexture(GL_TEXTURE0 + index);
    GLHelper::checkGLError("Textures glActiveTexture");
    glBindTexture(GL_TEXTURE_2D, mTextures[index]);
    GLHelper::checkGLError("Textures glBindTexture");
    if (changed){
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        GLHelper::checkGLError("Textures glTexImage2D");
    } else {
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, data);
        GLHelper::checkGLError("Textures glTexSubImage2D");
    }
}

void Textures::bindTexture(GLuint texttureId) {
    glBindTexture(GL_TEXTURE_2D, texttureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    GLHelper::checkGLError("glTextureParameteri - GL_TEXTURE_MIN_FILTER");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    GLHelper::checkGLError("glTextureParameteri - GL_TEXTURE_MAG_FILTER");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    GLHelper::checkGLError("glTextureParameteri - GL_TEXTURE_WRAP_S");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    GLHelper::checkGLError("glTextureParameteri - GL_TEXTURE_WRAP_T");
}

bool Textures::checkSizeChanged(unsigned int width, unsigned int height) {
    bool changed = false;
    if (width != mWidth || height != mHeight){
        mWidth = width;
        mHeight = height;
        changed = true;
    }
    return changed;
}

Textures::~Textures() {
    release();
}
