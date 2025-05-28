cmake_minimum_required(VERSION 3.31)
project(Syntho)

set(CMAKE_CXX_STANDARD 26)

add_executable(Syntho main.cpp)

set(CMAKE_CXX_CLANG_TIDY
        clang-tidy;
        -checks=*;
        -warnings-as-errors=*;)
