# Support Library for Arduino Devices

## Overview

This library is meant to provide different options to use Arduino and integrate use of different controls.

## HID Controller

The idea of the HidController is to provide the generic declarative API for simple HID devices.

```mermaid
classDiagram
    direction RL
    class Controller
    
    class Control {
        <<interface>>
        + setup() = 0
        + loop() = 0
    }
    
    class GenericControl {
        + ctor(HwApi&)
        + setup() = 0
        + loop() = 0
        - hw_api : HwApi
    }
    
    class RotaryEncoder {
        + ctor(dt, clk, sw)
        + setup()
        + loop()
        - pins
    }
    
    class DigitalPin {
        + ctor(pin)
        + setup()
        + loop()
    }
    
    class HwApi {
        + digitalRead(...)
        + digitalWrite(...)
        + pinMode(...)
    }
    
    class Callback {
        + operator()
    }
    
    GenericControl --|> Control : implements
    RotaryEncoder --|> GenericControl : implements
    DigitalPin --|> GenericControl : implements
    DigitalPin "3" --* "1" RotaryEncoder : 
    Control "*" --* "1" Controller
    HwApi "1" --o "1" GenericControl
```