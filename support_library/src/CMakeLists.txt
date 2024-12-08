cmake_minimum_required(VERSION 3.29)

add_library(support_library
        HwApiImpl.h
)

target_link_libraries(
        support_library
        api_library
        pins_library
        components_library
)

add_subdirectory(interfaces)
add_subdirectory(utilities)
add_subdirectory(pins)
add_subdirectory(components)
add_subdirectory(devices)