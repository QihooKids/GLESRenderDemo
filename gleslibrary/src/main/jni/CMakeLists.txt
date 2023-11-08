cmake_minimum_required(VERSION 3.4.1)

#添加编译选项参数
#add_compile_options(-DDLUA_DL_DLOPEN)

#按文件单个添加
#set(OPENGL_SRC, opengl/a.cpp opengl/b.cpp)

#按照目录器添加
include_directories(opengl)
aux_source_directory(opengl OPENGL_SRC)

include_directories(opengl/utils)
aux_source_directory(opengl/utils OPENGL_SRC_UTILES)
#通过list语法移除单个文件
#list(REMOVE_ITEM OPENGL_SRC "lua/lua.c")

#添加预编译宏
add_definitions(-DANDROID -DANDROID_NDK)

#单个文件添加
#add_library(cjson STATIC cjson/lua_cjson.c cjson/strbuf.c ${FPCONV_SOURCES})

#添加静态库
#add_library(opengl STATIC ${OPENGL_SRC})

#生成动态链接库
add_library(gles_render SHARED ${OPENGL_SRC} ${OPENGL_SRC_UTILES} GLJNI.c)

#查找系统库
find_library(log-lib log)
find_library(gles-lib GLESv2 )
find_library(android-lib android )

if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
    message("Target architecture is x86_64")
    # 在这里添加针对 x86_64 的配置
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm")
    message("Target architecture is ARM")
    # 在这里添加针对 ARM 的配置
else()
    message("Unknown target architecture: ${CMAKE_SYSTEM_PROCESSOR}")
    # 可能需要处理其他体系结构
endif()

target_link_libraries(gles_render  ${log-lib} ${gles-lib} ${android-lib})
