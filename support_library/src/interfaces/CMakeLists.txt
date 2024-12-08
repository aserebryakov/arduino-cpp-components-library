cmake_minimum_required(VERSION 3.29)

add_library(api_library STATIC
        HwApi.h
        HwApi.cpp
)

target_include_directories(api_library PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:>
)