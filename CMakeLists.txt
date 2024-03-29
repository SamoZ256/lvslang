cmake_minimum_required(VERSION 3.5)

project(lvslang)

option(BUILD_TESTS "Build tests" OFF)

set(CMAKE_CXX_STANDARD 17)

# -------- Main library and tools --------

# SPIRV-Tools
set(SPIRV-Headers_SOURCE_DIR ${PROJECT_SOURCE_DIR}/SPIRV-Headers)

add_subdirectory(${PROJECT_SOURCE_DIR}/SPIRV-Tools)

# LLVM
find_package(LLVM REQUIRED CONFIG)

llvm_map_components_to_libnames(LLVM_LIBS support core irreader passes)

# argumentum
set(ARGUMENTUM_BUILD_STATIC_LIBS ON)

add_subdirectory(${PROJECT_SOURCE_DIR}/argumentum)

# LVSLANG
add_library(lvslang_lib SHARED
    shader_ir_builder/common.cpp
    shader_ir_builder/block.cpp
    shader_ir_builder/air/type_handle.cpp
    shader_ir_builder/air/block.cpp
    shader_ir_builder/air/function.cpp
    shader_ir_builder/air/ir.cpp
    shader_ir_builder/spirv/type_value.cpp
    shader_ir_builder/spirv/function.cpp
    shader_ir_builder/spirv/ir.cpp
    src/common.cpp
    src/type_name.cpp
    src/ast.cpp
    src/ir_writer.cpp
    src/code_writer.cpp
    src/lvslang.cpp
    src/frontends/lvsl/lexer.cpp
    src/frontends/lvsl/parser.cpp
    src/frontends/metal/lexer.cpp
    src/frontends/metal/parser.cpp
)

target_include_directories(lvslang_lib PRIVATE ${PROJECT_SOURCE_DIR}/SPIRV-Tools/include ${PROJECT_SOURCE_DIR}/argumentum/include ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(lvslang_lib PUBLIC SPIRV-Tools SPIRV-Tools-opt Argumentum::argumentum)

target_include_directories(lvslang_lib PRIVATE ${LLVM_INCLUDE_DIRS})

target_link_libraries(lvslang_lib PUBLIC ${LLVM_LIBS})

add_executable(lvslang tools/lvslang.cpp)

target_include_directories(lvslang PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(lvslang PUBLIC lvslang_lib)

# -------- Embed standard libraries --------
add_executable(embed_standard_library src/embed_standard_library.cpp)

function (run_embed_standard_library name extension)
    set(BASE_NAME ${PROJECT_SOURCE_DIR}/src/frontends/${name}/standard_library)
    set(SOURCES ${BASE_NAME}/math.${extension} ${BASE_NAME}/textures.${extension})
    set(OUTPUT ${BASE_NAME}.inc)
    add_custom_command(
        OUTPUT ${OUTPUT}
        COMMAND embed_standard_library ${OUTPUT} ${SOURCES}
        DEPENDS embed_standard_library ${SOURCES}
        COMMENT "Embedding standard library for ${name} frontend"
    )

    add_custom_target(
        run_embed_standard_library_${name} ALL
        DEPENDS ${OUTPUT}
    )

    add_dependencies(lvslang_lib run_embed_standard_library_${name})
endfunction()

run_embed_standard_library(metal metal)
run_embed_standard_library(lvsl lvsl)

# -------- Tests --------
if (BUILD_TESTS)
    add_subdirectory(tests)
endif()
