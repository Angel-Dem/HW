cmake_minimum_required(VERSION 4.0)
project(hw_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(hw_1 main.cpp
        hw_2.cpp
        vector.cpp
        example.cpp
        singleton.h
        tracket_string.h
        wrapper.h)
