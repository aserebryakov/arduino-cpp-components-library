cmake_minimum_required(VERSION 3.29)

add_library(components_library STATIC
        RotaryEncoder.h
        RotaryEncoder.cpp
        Component.h
        Component.cpp
)

target_include_directories(components_library PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:>
)

target_link_libraries(
        components_library PUBLIC utilities_library pins_library
)