//
// Created by niu on 2023/11/7.
//

#include "RenderHelper.h"
#include "Render.h"

long createRender(unsigned int width, unsigned int height) {
    return reinterpret_cast<long >(new Render(width, height));
}

void release(long handle) {
    auto* render = reinterpret_cast<Render *>(handle);
    delete render;
}

unsigned int textureId(long handle){
    auto* render = reinterpret_cast<Render *>(handle);
    return render->textureId(0);
}

void render(long handle, unsigned char *data, int width, int height) {
    auto* render = reinterpret_cast<Render *>(handle);
    render->render(data, width, height);
}
