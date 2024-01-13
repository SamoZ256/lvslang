cmake_minimum_required(VERSION 3.5)

project(lvslang)

set(CMAKE_CXX_STANDARD 17)

set(SPIRV-Headers_SOURCE_DIR ${PROJECT_SOURCE_DIR}/SPIRV-Headers)

add_subdirectory(${PROJECT_SOURCE_DIR}/SPIRV-Tools)

find_package(LLVM REQUIRED CONFIG)

llvm_map_components_to_libnames(LLVM_LIBS support core irreader passes)

message("INCLUDE: ${LLVM_INCLUDE_DIRS}")
message("LIB: ${LLVM_LIBS}")

include_directories(${PROJECT_SOURCE_DIR}/SPIRV-Tools/include ${LLVM_INCLUDE_DIRS})

add_executable(lvslang
    src/main.cpp
    shader_ir_builder/common.cpp
    shader_ir_builder/spirv/value.cpp
)

target_link_libraries(lvslang PUBLIC SPIRV-Tools SPIRV-Tools-opt ${LLVM_LIBS})
