add_executable(tests main.cpp)

target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(tests PUBLIC lvslang_lib)
