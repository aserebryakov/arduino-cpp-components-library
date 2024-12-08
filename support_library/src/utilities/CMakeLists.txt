cmake_minimum_required(VERSION 3.29)

add_library(utilities_library STATIC
        Callback.h
        Callback.cpp
        HeapObject.h
        HeapObject.cpp
        Scheduler.h
        Scheduler.cpp
)

target_include_directories(utilities_library PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:>
)