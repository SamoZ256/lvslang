cmake_minimum_required(VERSION 3.5)

project(lvslang)

option(USE_LLVM "Use LLVM to assemble and optimize the output" ON)
option(BUILD_TESTS "Build tests" OFF)

set(CMAKE_CXX_STANDARD 17)

set(SPIRV-Headers_SOURCE_DIR ${PROJECT_SOURCE_DIR}/SPIRV-Headers)

add_subdirectory(${PROJECT_SOURCE_DIR}/SPIRV-Tools)

if (USE_LLVM)
    find_package(LLVM REQUIRED CONFIG)

    llvm_map_components_to_libnames(LLVM_LIBS support core irreader passes)

    add_compile_definitions(LVSLANG_USE_LLVM)
endif()

add_library(lvslang_lib SHARED
    shader_ir_builder/common.cpp
    shader_ir_builder/spirv/value.cpp
    src/lvslang.cpp
)

target_include_directories(lvslang_lib PRIVATE ${PROJECT_SOURCE_DIR}/SPIRV-Tools/include ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(lvslang_lib PUBLIC SPIRV-Tools SPIRV-Tools-opt)

if (USE_LLVM)
    target_include_directories(lvslang_lib PRIVATE ${LLVM_INCLUDE_DIRS})

    target_link_libraries(lvslang_lib PUBLIC ${LLVM_LIBS})
endif()

add_executable(lvslang tools/lvslang.cpp)

target_include_directories(lvslang PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(lvslang PUBLIC lvslang_lib)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()
