cmake_minimum_required(VERSION 3.29)

add_library(pins_library STATIC
        DigitalInputPin.h
        DigitalInputPin.cpp
        Pin.h
        Pin.cpp
)

target_include_directories(pins_library PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:>
)

target_link_libraries(
        pins_library PUBLIC api_library utilities_library
)