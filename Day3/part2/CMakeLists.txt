cmake_minimum_required(VERSION 3.10)

project(AOC2024_d3p2)

set(CMAKE_CXX_STANDARD 26)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_compile_options(-ggdb3)

add_executable(AOC2024_d3p2 main.cpp)
target_link_libraries(AOC2024_d3p2 PRIVATE stdc++exp)
