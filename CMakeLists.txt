cmake_minimum_required(VERSION 3.31)
project(Syntho)

set(CMAKE_CXX_STANDARD 26)

add_executable(Syntho src/main.cpp
        src/Oscillator.cpp
        include/Oscillator.h)

find_package(portaudio REQUIRED)

target_link_libraries(Syntho portaudio_static)

set(CMAKE_CXX_CLANG_TIDY
        clang-tidy;
        -checks=*;
        -warnings-as-errors=*;)
