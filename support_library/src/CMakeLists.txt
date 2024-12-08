cmake_minimum_required(VERSION 3.29)

add_library(api_library STATIC
        HwApi.h
        HwApi.cpp
)

add_library(utilities_library STATIC
        Callback.h
        Callback.cpp
        HeapObject.h
        HeapObject.cpp
        Scheduler.h
        Scheduler.cpp
)

add_library(pins_library STATIC
        DigitalInputPin.h
        DigitalInputPin.cpp
        Pin.h
        Pin.cpp
)

target_link_libraries(
        pins_library PUBLIC api_library utilities_library
)

add_library(components_library STATIC
        RotaryEncoder.h
        RotaryEncoder.cpp
        Component.h
        Component.cpp
)

target_link_libraries(
        components_library PUBLIC utilities_library pins_library
)

add_library(devices_library STATIC
        GenericController.h
        GenericController.cpp
)

target_link_libraries(
        devices_library PUBLIC utilities_library components_library
)

add_library(support_library STATIC
        HwApiImpl.h
)

target_link_libraries(
        support_library
        api_library
        pins_library
        components_library
)

target_include_directories(support_library PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:>
)
