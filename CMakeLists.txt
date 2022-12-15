cmake_minimum_required(VERSION 3.25)
project(iter)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -O3")

add_executable(experiments experiments.cpp)
add_test(experiments experiments)
