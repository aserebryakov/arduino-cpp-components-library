cmake_minimum_required(VERSION 3.29)
project(support_library)

set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(support_library
        Scheduler.cpp
        Scheduler.h
        Callback.cpp
        Callback.h
#        RotaryEncoder.cpp
#        RotaryEncoder.h
        DigitalPin.cpp
        DigitalPin.h
        HwApi.cpp
        HwApi.h
        HwApiImpl.h
        GenericController.cpp
        GenericController.h
        HeapObject.cpp
        HeapObject.h
        Control.cpp
        Control.h
)

add_subdirectory(test)