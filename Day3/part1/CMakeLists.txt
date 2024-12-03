cmake_minimum_required(VERSION 3.10)

project(AOC2024_d3p1)

set(CMAKE_CXX_STANDARD 26)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_compile_options(-ggdb3)

add_executable(AOC2024_d3p1 main.cpp)
target_link_libraries(AOC2024_d3p1 PRIVATE stdc++exp)
