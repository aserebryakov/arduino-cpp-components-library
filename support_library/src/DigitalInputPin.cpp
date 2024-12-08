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

#include "DigitalInputPin.h"
#include "Utilities.h"

DigitalInputPin::DigitalInputPin(InputPinConfig&& pin_config, HwApi& hw_api) : DigitalInputPin{
    utilities::move(pin_config), {}, {}, hw_api} {
}

DigitalInputPin::DigitalInputPin(InputPinConfig&& pin_config, Callback&& on_low_high_change,
                                 Callback&& on_high_low_change, HwApi& hwapi) : hw_api{hwapi}, config{pin_config},
    on_low_high_change_callback{on_low_high_change}, on_high_low_change_callback{on_high_low_change} {
}

PIN_CHANGE DigitalInputPin::getPinChange() const {
    if (previous_level == current_level) {
        return PIN_CHANGE::NONE;
    }

    if (previous_level == HwApi::LEVEL_HIGH && current_level == HwApi::LEVEL_LOW) {
        return PIN_CHANGE::HIGH_LOW;
    }

    return PIN_CHANGE::LOW_HIGH;
}

void DigitalInputPin::begin() {
    hw_api.pinMode(config.getPin(), config.isPullup() ? HwApi::PIN_MODE::INPUT_PULLUP_MODE : HwApi::PIN_MODE::INPUT_MODE);
}

void DigitalInputPin::loop() {
    read();

    if (getPinChange() == PIN_CHANGE::HIGH_LOW) {
        on_high_low_change_callback();
    }

    if (getPinChange() == PIN_CHANGE::LOW_HIGH) {
        on_low_high_change_callback();
    }
}

HwApi::DIGITAL_PIN_LEVEL DigitalInputPin::read() {
    previous_level = current_level;
    current_level = hw_api.digitalRead(config.getPin()) == HwApi::LEVEL_HIGH ? HwApi::LEVEL_HIGH : HwApi::LEVEL_LOW;
    return current_level;
}

HwApi::DIGITAL_PIN_LEVEL DigitalInputPin::getLevel() const {
    return current_level;
}
