cmake_minimum_required(VERSION 3.5)

project(lvslang)

option(USE_LLVM "Use LLVM to assemble and optimize the output" ON)
option(BUILD_TESTS "Build tests" OFF)

set(CMAKE_CXX_STANDARD 17)

# -------- Main library and tools --------

# SPIRV-Tools
set(SPIRV-Headers_SOURCE_DIR ${PROJECT_SOURCE_DIR}/SPIRV-Headers)

add_subdirectory(${PROJECT_SOURCE_DIR}/SPIRV-Tools)

# LLVM
if (USE_LLVM)
    find_package(LLVM REQUIRED CONFIG)

    llvm_map_components_to_libnames(LLVM_LIBS support core irreader passes)

    add_compile_definitions(LVSLANG_USE_LLVM)
endif()

# argumentum
set(ARGUMENTUM_BUILD_STATIC_LIBS ON)

add_subdirectory(${PROJECT_SOURCE_DIR}/argumentum)

# LVSLANG
add_library(lvslang_lib SHARED
    shader_ir_builder/common.cpp
    shader_ir_builder/spirv/value.cpp
    src/lvslang.cpp
)

target_include_directories(lvslang_lib PRIVATE ${PROJECT_SOURCE_DIR}/SPIRV-Tools/include ${PROJECT_SOURCE_DIR}/argumentum/include ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(lvslang_lib PUBLIC SPIRV-Tools SPIRV-Tools-opt Argumentum::argumentum)

if (USE_LLVM)
    target_include_directories(lvslang_lib PRIVATE ${LLVM_INCLUDE_DIRS})

    target_link_libraries(lvslang_lib PUBLIC ${LLVM_LIBS})
endif()

add_executable(lvslang tools/lvslang.cpp)

target_include_directories(lvslang PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(lvslang PUBLIC lvslang_lib)

# -------- Embed standard libraries --------
add_executable(embed_standard_library src/embed_standard_library.cpp)

function (run_embed_standard_library name)
    set(PATH_WITHOUT_EXTENSION ${PROJECT_SOURCE_DIR}/include/lvslang/frontends/${name}/standard_library)
    add_custom_command(
        OUTPUT ${PATH_WITHOUT_EXTENSION}.inc
        COMMAND embed_standard_library ${PATH_WITHOUT_EXTENSION}.${name} ${PATH_WITHOUT_EXTENSION}.inc
        DEPENDS embed_standard_library ${PATH_WITHOUT_EXTENSION}.${name}
        COMMENT "Embedding standard library ${name}"
    )

    add_custom_target(
        run_embed_standard_library_${name} ALL
        DEPENDS ${PATH_WITHOUT_EXTENSION}.inc
    )

    add_dependencies(lvslang_lib run_embed_standard_library_${name})
endfunction()

run_embed_standard_library(metal)
run_embed_standard_library(lvsl)

# -------- Tests --------
if (BUILD_TESTS)
    add_subdirectory(tests)
endif()
