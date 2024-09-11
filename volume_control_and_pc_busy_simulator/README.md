# Volume Control with PC Busy

## Idea

To build a device that will contain following functionalities:

  * Volume control (volume up, volume down, mute)
  * Mouse move emulator
  * Keyboard input emulator

## User Interface

  * 5-pin rotary encoder to control volume
  * button to turn on/off mouse move emulation (with status LED)
  * button to turn on/off keyboard input emulation (with status LED)

### Software Design

```mermaid
---
title: Rotary Encoder
---
classDiagram
    class PIN_CHANGE {
        <<enumeration>>
        LOW_HIGH,
        HIGH_LOW,
        NO_CHANGE
    }

    class RotaryEncoderPin {
        <<interface>>
        + readPinChange() PIN_CHANGE
        + readPinStatus() bool
    }

    class RotaryEncoderPinImpl {
        + ctor(number, pin_mode)
    }

    class RotaryEncoderPinMock

    class RotaryEncoder {
        + ctor(dt_pin, clk_pin, sw_pin)
        + setTurnClockwiseHandler()
        + setTurnCounterClockwiseHandler()
        + setPushButtonHandler()
        + readStatus()
        - onClockwise
        - onCounterClockwise
        - onPushButton
        - dt_pin : RotaryEncoderPin
        - clk_pin : RotaryEncoderPin
        - sw_pin : RotaryEncoderPin
    }

    PIN_CHANGE --> RotaryEncoderPin

    RotaryEncoderPin <|-- RotaryEncoderPinImpl
    RotaryEncoderPin <|-- RotaryEncoderPinMock

    RotaryEncoder *-- RotaryEncoderPin
```

### Mouse Emulator Scheduling Example

```mermaid
sequenceDiagram
    participant Scheduler
    participant Controller
    participant RotaryEncoder
    participant MouseEmulator

    loop
        Controller ->> RotaryEncoder : readStatus()
        activate RotaryEncoder
        note over RotaryEncoder : call handlers
        RotaryEncoder -->> Controller : 
        deactivate RotaryEncoder

        Controller ->> MouseEmulator : readStatus()
        activate MouseEmulator

        alt START
            MouseEmulator -->> Controller : 
            Controller ->> Scheduler : addTask(mouse_callback)
            Scheduler -->> Controller : 
        else STOP
            MouseEmulator -->> Controller : 
            deactivate MouseEmulator
            Controller ->> Scheduler : removeTask(mouse_callback)
            Scheduler -->> Controller : 
        end
        
        Controller ->> Scheduler : tick(10ms)
        Scheduler -->> Controller : 
        
        note over Controller : delay(10ms)
    end
```
