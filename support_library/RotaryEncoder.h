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
#include "DigitalPin.h"
#include "HwApi.h"
#include "Control.h"

/**
 * Implements rotary encoder functionality.
 */
class RotaryEncoder : public Control {
public:
    /**
      * Constructor.
      *
      * @param dt_pin DT pin
      * @param clk_pin CLK pin
      * @param sw_pin SW pin
      * @param on_turn_clockwise clockwise turn callback
      * @param on_turn_counterclockwise counterclockwise turn callback
      * @param on_push_button push button callback
      */
    RotaryEncoder(DigitalPin&& dt_pin, DigitalPin&& clk_pin, DigitalPin&& sw_pin, Callback&& on_turn_clockwise = {},
                  Callback&& on_turn_counterclockwise = {}, Callback&& on_push_button = {});


    virtual ~RotaryEncoder() override = default;

    /**
     * Reads pins levels and calls callbacks.
     */
    void readPins();

    void setup() override;
    void loop() override;

private:
    void readRotation();

    DigitalPin dt_pin;
    DigitalPin clk_pin;
    DigitalPin sw_pin;
    Callback on_turn_clockwise{};
    Callback on_turn_counterclockwise{};
    Callback on_push_button{};
};

#endif //ROTARYENCODER_H
