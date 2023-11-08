//
// Created by niu on 2023/11/3.
//

#include "Render.h"
#include "ProgramFactory.h"
#include "Logs.h"

GLfloat gVertexsCoords[] = {
        -1.0, -1.0, // (L, B)
        1.0, -1.0,  // (R, B)
        -1.0, 1.0,  // (L, T)
        1.0, 1.0,   // (R, T)
};

GLfloat gTextureCoords[] = {
        0.0, 1.0, // (L, T)
        1.0, 1.0, // (R, T)
        0.0, 0.0, // (L, B)
        1.0, 0.0, // (R, B)
};

Render::Render(unsigned int width, unsigned int height)
        : mWidth(width), mHeight(height){
    ksMatrixLoadIdentity(&mMatrix);
    mTextures = new Textures(NUM_TEXTURE, mTextureIds);
    mTextures->init();
    logD("Render created....");
}

Render::~Render() {
    delete mTextures;
    delete mProgram;
    logD("Render released....");
}

void Render::render(unsigned char *data, GLint width, GLint height) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    if(!mProgram){
        mProgram = ProgramFactory::createProgram();
        mProgram->initialize();
    }
    glViewport(0, 0, mWidth, mHeight);
    mProgram->updateVertexCoords(gVertexsCoords);
    mProgram->updateMatrix(reinterpret_cast<const float *>(mMatrix.m));
    mTextures->loadTexture(0, data, GL_RGBA, width, height);
    mProgram->updateTextureCoords(gTextureCoords);
    glDrawArrays(GL_TRIANGLE_STRIP, 0 ,4);
    glUseProgram(0);
}
