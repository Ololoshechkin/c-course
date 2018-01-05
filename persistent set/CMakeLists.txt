cmake_minimum_required(VERSION 2.8)
project(persistent_set)

include(ExternalProject)

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

ExternalProject_Add(googletest
    GIT_REPOSITORY https://github.com/google/googletest
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)

include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

add_executable(${PROJECT_NAME} main.cpp persistent_set.h my_shared_ptr.h my_linked_ptr.h unit_test.h persistent_set.h fast_rand.cpp fast_rand.h)
add_dependencies(persistent_set googletest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fsanitize=undefined -D_GLIBCXX_DEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=undefined -Wall -Wextra -pedantic  -Wformat=2")
target_link_libraries (${PROJECT_NAME} gtest gmock)