cmake_minimum_required(VERSION 2.8)

project(pointers_test)

FIND_PACKAGE( Boost 1.66.0 COMPONENTS REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_executable(${PROJECT_NAME} main.cpp abstract_test.h alloc_dealloc_test.h decart_tree_test.h equasion_and_copy_test.h linked_ptr.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++1z")

TARGET_LINK_LIBRARIES(${PROJECT_NAME} LINK_PUBLIC ${Boost_LIBRARIES} )