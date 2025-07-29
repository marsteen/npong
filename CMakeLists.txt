cmake_minimum_required(VERSION 3.10)
project("npong")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -O2")

set(OpenGL_GL_PREFERENCE "GLVND")

add_compile_options("-Wno-deprecated")

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIR})

find_package(ZLIB REQUIRED)
include_directories(${ZLIB_INCLUDE_DIR})

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})


set(EXECUTABLE_OUTPUT_PATH ../distribution)

include_directories(./source)

add_executable(${CMAKE_PROJECT_NAME}
./source/pong/main.cpp
./source/pong/CPong.cpp
./source/pong/CSdlApp.cpp
./source/pong/CSdlSound.cpp
./source/pong/CSdlPong.cpp
./source/pong/CSprite.cpp
./source/pong/CPolylineObject.cpp
./source/pong/CBoundingObject.cpp
./source/pong/CVectorShape.cpp
./source/pong/SShapeParams.cpp
./source/pong/CGame_Read.cpp
./source/pong/CVectorUnit.cpp
./source/pong/CPlayerUnit.cpp
./source/pong/CEnemyUnit.cpp
./source/pong/CBaitUnit.cpp
./source/pong/CVectorShot.cpp
./source/pong/CExplosion.cpp
./source/pong/CDebrisUnit.cpp
./source/pong/CVectorObject.cpp
./source/file/CFileIO.cpp           
./source/tools/CStringTool.cpp
./source/tools/CRandom.cpp
./source/tools/CKeymap.cpp
./source/cgl/CGL_Texture.cpp
./source/cgl/CGL_Patch2d.cpp
./source/cgl/CGL_OpenGL.cpp
./source/cgl/CGL_SaveScreen.cpp
./source/cgl/CGL_FramebufferObject.cpp
./source/cgl/NGLprimitives.cpp
./source/shader/CGL_NGO_Shader.cpp
./source/shader/CGL_NGO_BlurShader.cpp
./source/graflib/CGraflib.cpp
./source/graflib/CGraflibTga.cpp
./source/graflib/CGraflibPng.cpp
./source/graflib/CPixel24.cpp
./source/graflib/CPixel32.cpp
./source/global/GlobalSystemFunctions.cpp
./source/global/GlobalDebug.cpp
./source/mvpng/mv_graphics_png.c
./source/stb/stb_vorbis.c
)

target_link_libraries(${CMAKE_PROJECT_NAME}
    ${OPENGL_LIBRARIES}
    GLEW::GLEW
    ${SDL2_LIBRARIES}
    ${PNG_LIBRARY}
    ${JPEG_LIBRARY}
    ZLIB::ZLIB
)





