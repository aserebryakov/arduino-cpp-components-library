// MIT License
//
// Copyright (c) 2024 Alexander Serebryakov
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef ROTARYENCODER_H
#define ROTARYENCODER_H

#include "Callback.h"

enum class PIN_CHANGE {
    LOW_HIGH,
    HIGH_LOW,
    NONE
};

class RotaryEncoderPin {
public:
    virtual ~RotaryEncoderPin() = default;
    virtual PIN_CHANGE readPinChange() = 0;
    virtual bool readPinStatus() = 0;
};


class RotaryEncoder {
public:
    RotaryEncoder(RotaryEncoderPin& dt_pin, RotaryEncoderPin& clk_pin, RotaryEncoderPin& sw_pin);
    void readRotation();
    void readStatus();

    void setTurnClockwiseCallback(Callback&& callback);
    void setTurnCounterClockwiseCallback(Callback&& callback);
    void setPushButtonCallback(Callback&& callback);

private:
    RotaryEncoderPin& dt_pin;
    RotaryEncoderPin& clk_pin;
    RotaryEncoderPin& sw_pin;
    Callback on_turn_clockwise{};
    Callback on_turn_counterclockwise{};
    Callback on_push_button{};
};

#endif //ROTARYENCODER_H
