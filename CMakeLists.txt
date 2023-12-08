cmake_minimum_required(VERSION 3.1.3.26)

project(lvslang)

set(CMAKE_CXX_STANDARD 20)

add_executable(lvslang
    src/main.cpp
    shader_ir_builder/common.cpp
    shader_ir_builder/spirv/value.cpp
)
