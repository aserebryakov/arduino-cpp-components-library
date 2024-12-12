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

#include "RotaryEncoder.h"
#include "Utilities.h"

RotaryEncoder::RotaryEncoder(InputPinConfig&& dt_pin, InputPinConfig&& clk_pin, InputPinConfig&& sw_pin, HwApi& hw_api,
                             Callback&& on_turn_clockwise, Callback&& on_turn_counterclockwise,
                             Callback&& on_push_button) : dt_pin{utilities::move(dt_pin), hw_api},
                                                          clk_pin{utilities::move(clk_pin), hw_api},
                                                          sw_pin{utilities::move(sw_pin), hw_api},
                                                          on_turn_clockwise{on_turn_clockwise},
                                                          on_turn_counterclockwise{on_turn_counterclockwise},
                                                          on_push_button{on_push_button} {
}

void RotaryEncoder::readPins() {
    readRotation();

    sw_pin.read();
    if (sw_pin.getPinChange() == PIN_CHANGE::HIGH_LOW) {
        on_push_button();
    }
}

void RotaryEncoder::readRotation() {
    dt_pin.read();
    clk_pin.read();

    if (dt_pin.getPinChange() != PIN_CHANGE::LOW_HIGH) {
        return;
    }

    if (clk_pin.getLevel() == HwApi::LEVEL_HIGH) {
        on_turn_counterclockwise();
    }
    else {
        on_turn_clockwise();
    }
}

void RotaryEncoder::begin() {
    dt_pin.begin();
    clk_pin.begin();
    sw_pin.begin();
}

void RotaryEncoder::loop() {
    readPins();
}
