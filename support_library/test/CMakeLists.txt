cmake_minimum_required(VERSION 3.29)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        support_library_test
        SchedulerTest.cpp
        RotaryEncoderTest.cpp
        HwApiMock.cpp
        HwApiMock.h
        DigitalPinTest.cpp
)

include(GoogleTest)

target_link_libraries(
        support_library_test
        support_library
        GTest::gmock_main
)

enable_testing()

gtest_discover_tests(support_library_test)
