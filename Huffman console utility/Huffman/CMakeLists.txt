cmake_minimum_required(VERSION 3.6)
project(Huffman)

set(CMAKE_CXX_STANDARD 14)

include_directories(${Huffman_SOURCE_DIR})
include_directories(${Huffman_SOURCE_DIR}/../HuffmanLibrary)

add_library(huffman_lib
        binary_code.h
        binary_code.cpp
        huffman_tree.h
        huffman_tree.cpp
        huffman_archiver.h
        huffman_archiver.cpp
        )

install(TARGETS huffman_lib DESTINATION lib)
install (FILES
        binary_code.h
        huffman_tree.h
        huffman_archiver.h
        DESTINATION include/huffman)

set(SOURCE_FILES main.cpp)
add_executable(Huffman ${SOURCE_FILES})