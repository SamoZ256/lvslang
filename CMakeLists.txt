cmake_minimum_required(VERSION 3.5)

project(lvslang)

option(USE_LLVM "Use LLVM to assemble and optimize the output" ON)

set(CMAKE_CXX_STANDARD 17)

set(SPIRV-Headers_SOURCE_DIR ${PROJECT_SOURCE_DIR}/SPIRV-Headers)

add_subdirectory(${PROJECT_SOURCE_DIR}/SPIRV-Tools)

include_directories(${PROJECT_SOURCE_DIR}/SPIRV-Tools/include)

if (USE_LLVM)
    find_package(LLVM REQUIRED CONFIG)

    llvm_map_components_to_libnames(LLVM_LIBS support core irreader passes)

    include_directories(${LLVM_INCLUDE_DIRS})

    add_compile_definitions(LVSLANG_USE_LLVM)
endif()

add_executable(lvslang
    src/main.cpp
    shader_ir_builder/common.cpp
    shader_ir_builder/spirv/value.cpp
)

target_link_libraries(lvslang PUBLIC SPIRV-Tools SPIRV-Tools-opt)

if (USE_LLVM)
    target_link_libraries(lvslang PUBLIC ${LLVM_LIBS})
endif()
