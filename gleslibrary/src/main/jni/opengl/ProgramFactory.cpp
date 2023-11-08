//
// Created by niu on 2023/11/7.
//

#include "ProgramFactory.h"

Program* ProgramFactory::createProgram() {
    return new Program();
}
