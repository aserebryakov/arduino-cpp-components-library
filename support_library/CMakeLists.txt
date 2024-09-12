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

enable_testing()

add_library(support_library
    Scheduler.cpp
    Scheduler.h
)

add_executable(
        support_library_test
        SchedulerTest.cpp
)

target_link_libraries(
        support_library_test
        support_library
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(support_library_test)