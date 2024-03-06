cmake_minimum_required(VERSION 3.26)
project(saper)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -pedantic)
add_executable(saper main.cpp
        MinesweeperBoard.cpp
        MinesweeperBoard.h
)
