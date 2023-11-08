#if defined(ANDROID)
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#else
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#endif
#include "GLHelper.h"
#include "Logs.h"

bool GLHelper::checkGLError(const char *opName) {
    bool hasError = false;
    GLenum error = glGetError();
    while (error){
       logE("After opration %s gl error(0x%x)\n", opName, error);
       error = glGetError();
       hasError = true;
    }
    return hasError;
}