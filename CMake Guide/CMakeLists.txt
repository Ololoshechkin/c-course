cmake_minimum_required(VERSION 2.8) // мин. версия

project(BIGINT) // project(XXX) создает неявно много равзных переменных, в т.ч.
 
include_directories(${BIGINT_SOURCE_DIR})

add_executable(big_integer_testing
               big_integer_testing.cpp
               big_integer.h
               big_integer.cpp
               gtest/gtest-all.cc
               gtest/gtest.h
               gtest/gtest_main.cc) //добавляет executable файлы

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX) 
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pedantic") // флаги компиляции
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif()

target_link_libraries(big_integer_testing -lgmp -lgmpxx -lpthread) // линкуем с библиотеками gmp, lgmpxx, pthread

// NB: основное предназначение build-системы — собирать проект и пересобирать. И в случае пересборки просекать зависимости в файлов и менять только их