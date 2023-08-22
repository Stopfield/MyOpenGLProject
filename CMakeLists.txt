cmake_minimum_required(VERSION 3.6.0)
project(my_opengl VERSION 0.1.0)

cmake_policy(SET CMP0072 NEW)

add_executable(my_opengl
    src/main.cpp
    src/glad.h
    src/glad.c
    src/Shader.h
    src/stb_image.h
)

find_package(OpenGL REQUIRED) 

target_link_libraries(my_opengl 
    glfw
    OpenGL::GL
)