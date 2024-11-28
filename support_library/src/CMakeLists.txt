cmake_minimum_required(VERSION 3.29)

add_library(support_library
        Scheduler.cpp
        Scheduler.h
        Callback.cpp
        Callback.h
        RotaryEncoder.cpp
        RotaryEncoder.h
        DigitalPin.cpp
        DigitalPin.h
        HwApi.cpp
        HwApi.h
        HwApiImpl.h
        GenericController.cpp
        GenericController.h
        HeapObject.cpp
        HeapObject.h
        Hardware.cpp
        Hardware.h
        DeviceApi.cpp
        DeviceApi.h
)