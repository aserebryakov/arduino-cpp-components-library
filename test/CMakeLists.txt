cmake_minimum_required(VERSION 3.29)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        cpp_components_test
        SchedulerTest.cpp
        RotaryEncoderTest.cpp
        HwApiMock.cpp
        HwApiMock.h
        DigitalInputPinTest.cpp
        GenericControllerTest.cpp
        HeapObjectTest.cpp
        ButtonTest.cpp
        DigitalOutputPinTest.cpp
        DigitalLedTest.cpp
)

include(GoogleTest)

target_link_libraries(
        cpp_components_test
        cpp_components_library
        api_library
        devices_library
        GTest::gmock_main
)

enable_testing()

gtest_discover_tests(cpp_components_test)
