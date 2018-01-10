cmake_minimum_required(VERSION 3.8)
project(lab3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp wav_header.hpp wav_core.hpp wav_exceptions.hpp wav_core.cpp)
add_executable(lab3 ${SOURCE_FILES} wav_header.hpp wav_core.hpp wav_exceptions.hpp wav_core.cpp)