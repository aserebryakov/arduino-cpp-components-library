cmake_minimum_required(VERSION 3.29)

add_library(devices_library STATIC
        GenericController.h
        GenericController.cpp
)

target_include_directories(devices_library PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:>
)

target_link_libraries(
        devices_library PUBLIC utilities_library components_library
)