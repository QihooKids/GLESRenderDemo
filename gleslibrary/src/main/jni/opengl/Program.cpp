//
// Created by niu on 2023/11/6.
//

#include <cstdlib>
#include "Program.h"
#include "Shader.h"
#include "Logs.h"
#include "GLHelper.h"

const char *Program::getVertextShaderSource() const {
    return
            "attribute vec4 position;"
            "attribute vec2 texCoord;"
            "uniform mat4 matrix;"
            "varying vec2 tc;"
            "void main()"
            "{"
            "   gl_Position = position * matrix;"
            "   tc = texCoord;"
            "}";
}

const char *Program::getFragmentShaderSource() const {
    return
            "precision mediump float;"
            "varying lowp vec2 tc;"
            "uniform sampler2D Sampler;"
            "void main()"
            "{"
            "   gl_FragColor = texture2D(Sampler, tc);"
            "}";
}

Program::Program()
        : mProgramId(0), mVertexCoordIndex(-1), mTextureCoordIndex(-1), mMetrixIndex(-1),
          mTexIndex(-1) {
}

Program::~Program() {
    if (mProgramId > 0) {
        glDeleteProgram(mProgramId);
    }
}

bool Program::initialize() {
    mProgramId = loadProgram();
    return mProgramId != 0 && onInit();
}

bool Program::onInit() {
    mVertexCoordIndex = glGetAttribLocation(mProgramId, "position");
    if (!GLHelper::checkGLError("ImageFilter position \n")) {
        mTextureCoordIndex = glGetAttribLocation(mProgramId, "texCoord");
        if (!GLHelper::checkGLError("ImageFilter texCoord \n")) {
            mMetrixIndex = glGetUniformLocation(mProgramId, "matrix");
            if (!GLHelper::checkGLError("ImageFilter matrix \n")) {
                GLint tex = glGetUniformLocation(mProgramId, "Sampler");
                if (!GLHelper::checkGLError("ImageFilter Sampler \n")) {
                    // glUniform1i调用前需调用glUseProgram
                    glUseProgram(mProgramId);
                    mTexIndex = tex;
                    glUniform1i(mTexIndex, 0);
                    return true;
                }
            }
        }
    }
    return false;
}

unsigned int Program::loadProgram() {
    GLuint program = 0;
    Shader vShader(getVertextShaderSource(), GL_VERTEX_SHADER);
    if (vShader.loadShader() != 0) {
        Shader fShader(getFragmentShaderSource(), GL_FRAGMENT_SHADER);
        if (fShader.loadShader() != 0) {
            program = glCreateProgram();
            if (program != 0) {
                glAttachShader(program, vShader.shader());
                glAttachShader(program, fShader.shader());
                glLinkProgram(program);
                GLint linked = 0;
                glGetProgramiv(program, GL_LINK_STATUS, &linked);
                if (!linked) {
                    printErrorInfo(vShader, fShader, program);
                }
            }
            glDeleteShader(fShader.shader());
        }
        glDeleteShader(vShader.shader());
    }
    return program;
}

void Program::printErrorInfo(const Shader &vShader, const Shader &fShader, GLuint program) {
    GLint infoLen = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
    if (infoLen > 1) {
        char *infoLog = (char *) malloc(sizeof(char) * (infoLen + 1));
        if (infoLog) {
            glGetProgramInfoLog(program, infoLen, NULL, infoLog);
            infoLog[infoLen] = '\0';
            logE("Could not link mProgram:\n%s\n", infoLog);
            free(infoLog);
        }
    }
    glDetachShader(program, vShader.shader());
    glDeleteShader(vShader.shader());
    glDetachShader(program, fShader.shader());
    glDeleteShader(fShader.shader());
    glDeleteProgram(program);
    logE("Could not glLinkProgram\n");
}

void Program::updateVertexCoords(const float *vertexCoords) {
    glUseProgram(mProgramId);
    glEnableVertexAttribArray(mVertexCoordIndex);
    glVertexAttribPointer(mVertexCoordIndex, 2, GL_FLOAT, 0, 0, vertexCoords);
}

void Program::updateTextureCoords(const float *textureCoords) {
    glEnableVertexAttribArray(mTextureCoordIndex);
    glVertexAttribPointer(mTextureCoordIndex, 2, GL_FLOAT, 0, 0, textureCoords);
    glUniform1i(mTexIndex, 0);
}

void Program::updateMatrix(const float *matrix) {
    glUniformMatrix4fv(mMetrixIndex, 1, GL_FALSE, matrix);
}

