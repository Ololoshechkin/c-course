cmake_minimum_required(VERSION 2.8)

project(persistent_set)
add_executable(${PROJECT_NAME} main.cpp persistent_set.h my_shared_ptr.h my_linked_ptr.h unit_test.h)

#set (gtest_disable_pthreads on)
add_subdirectory (googletest)
#config_compiler_and_linker()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fsanitize=address,undefined -D_GLIBCXX_DEBUG -DCMAKE_CXX_COMPILER=g++-6")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -Wall -Wextra -pedantic  -Wformat=2 -DCMAKE_CXX_COMPILER=g++-6")
target_link_libraries (${PROJECT_NAME} gtest gmock)