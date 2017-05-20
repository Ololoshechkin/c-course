cmake_minimum_required(VERSION 3.6)
project(Huffman)

set(CMAKE_CXX_STANDARD 14)

include_directories(${Huffman_SOURCE_DIR})

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
        DESTINATION include/huffman_lib)

add_executable(Huffman
	main.cpp
        binary_code.h
        binary_code.cpp
        huffman_tree.h
        huffman_tree.cpp
        huffman_archiver.h
        huffman_archiver.cpp
        exceptions.cpp
        exceptions.h
        )
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -std=c++14 -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fsanitize=address,undefined")
endif()
target_link_libraries(huffman_lib)