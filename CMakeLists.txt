cmake_minimum_required(VERSION 3.5)

project(cxx_embedder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cxx_embedder main.cpp)

target_link_libraries(cxx_embedder ${CMAKE_CURRENT_SOURCE_DIR}/python/LIBS/python3.lib)
target_link_libraries(cxx_embedder ${CMAKE_CURRENT_SOURCE_DIR}/python/LIBS/python39.lib)
target_link_libraries(cxx_embedder ${CMAKE_CURRENT_SOURCE_DIR}/python/LIBS/python39_d.lib)
