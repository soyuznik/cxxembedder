cmake_minimum_required(VERSION 3.5)

project(cxx_embedder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cxx_embedder main.cpp)

target_link_libraries(cxx_embedder ${CMAKE_CURRENT_SOURCE_DIR}/cxxembedder/_cxxlib/python3.lib)
target_link_libraries(cxx_embedder ${CMAKE_CURRENT_SOURCE_DIR}/cxxembedder/_cxxlib/python39.lib)
target_link_libraries(cxx_embedder ${CMAKE_CURRENT_SOURCE_DIR}/cxxembedder/_cxxlib/python39_d.lib)
target_link_libraries(cxx_embedder ${CMAKE_CURRENT_SOURCE_DIR}/cxxembedder/_cxxlib/liblua54.a)
target_link_libraries(cxx_embedder ${CMAKE_CURRENT_SOURCE_DIR}/cxxembedder/_cxxlib/libangelscript.mingw.a)
target_link_libraries(cxx_embedder ${CMAKE_CURRENT_SOURCE_DIR}/cxxembedder/_cxxlib/node.lib)

