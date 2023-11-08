//
// Created by niu on 2023/11/3.
//

#ifndef ANDROID_RENDER_H
#define ANDROID_RENDER_H

#include "GLESMath.h"
#include "Textures.h"
#include "Program.h"

const unsigned int NUM_TEXTURE = 1;
class Render{
public:
    Render(unsigned int width, unsigned int height);
    ~Render();

public:
    void render(unsigned char *data, GLint width, GLint height);
private:
    unsigned int mWidth;
    unsigned int mHeight;
    KSMatrix4 mMatrix{};
    unsigned int mTextureIds[NUM_TEXTURE];
    Textures *mTextures;
    Program *mProgram{};
};
#endif //ANDROID_RENDER_H
