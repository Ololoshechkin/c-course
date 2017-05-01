cmake_minimum_required(VERSION 3.6)
project(HuffmanLibrary)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES huffman_tree.cpp huffman_tree.h letter_counter.h huffman_archiver.cpp huffman_archiver.h binary_code.cpp binary_code.h)
add_library(HuffmanLibrary SHARED ${SOURCE_FILES})