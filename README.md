# Support Library for Arduino Devices

## Overview

This library is meant to provide different options to use Arduino or other compatible controllers and integrate use of
different devices (rotary encoders, buttons, switches).

## Abstraction Levels

There are following levels of abstractions:

  1. Raw API
  2. Support library hardware API facade
  3. Pins
  4. Components
  5. Devices

### Raw Arduino API

Direct usage of Arduino API functions like `pinMode()`, `digitalRead()` etc.

### Support library hardware API facade

This is a facade to isolate Arduino API calls.

It provides the possibility of mocking these interfaces for the purpose of components unit testing.

```mermaid
classDiagram
    class HwApi {
        <<interface>>
        + digitalRead(...)
        + digitalWrite(...)
        + pinMode(...)
    }
```

### Pins

Abstraction level that represents pins and work with them.

```mermaid
classDiagram
    class PinApi {
        <<interface>>
        + begin() = 0
        + loop() = 0
    }

    class DigitalInputPin {
        + begin()
        + loop()
    }

    class DigitalOutputPin {
        + begin()
        + loop()
    }

    class AnalogInputPin {
        + begin()
        + loop()
    }

    class AnalogOutputPin {
        + begin()
        + loop()
    }

    DigitalInputPin --|> PinApi : implements
    DigitalOutputPin --|> PinApi : implements
    AnalogInputPin --|> PinApi : implements
    AnalogOutputPin --|> PinApi : implements
```

### Components

Component is a composition of pins that has clear real life functional representation:

  * encoder
  * switch
  * button
  * etc.

```mermaid
classDiagram
    class HwComponentApi {
        <<interface>>
        + begin() = 0
        + loop() = 0
    }
    
    class DigitalInputPin {
        + begin()
        + loop()
    }

    class Button {
        + begin()
        + loop()
    }

    class RotaryEncoder {
        + ctor(dt, clk, sw)
        + begin()
        + loop()
    }

    DigitalInputPin "1" --* "1" Button
    DigitalInputPin "3" --* "1" RotaryEncoder

    class DigitalOutputPin {
        + begin()
        + loop()
    }

    class Led {
        + begin()
        + loop()
    }

    DigitalOutputPin "1" --* "1" Led
    RotaryEncoder --|> HwComponentApi : implements
    Led --|> HwComponentApi : implements
    Button --|> HwComponentApi : implements
```

### Devices

Device is a composition of components providing a specific functionality to user (e.g. volume control, gamepad, 
mouse, etc.).

```mermaid
classDiagram
    class HwDeviceApi {
        <<interface>>
        + begin() = 0
        + loop() = 0
    }
    
    class VolumeControl {
        + begin()
        + loop()
    }
    
    VolumeControl --|> HwDeviceApi : implements
    RotaryEncoder "1" --* "1" VolumeControl
```