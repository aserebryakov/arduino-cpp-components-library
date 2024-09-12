cmake_minimum_required(VERSION 3.29)
project(arduino_fun)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(support_library)

add_library(arduino_fun
        library.cpp)

target_link_libraries(arduino_fun support_library)