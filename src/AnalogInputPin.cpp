// MIT License
//
// Copyright (c) 2026 Alexander Serebryakov
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

#include "AnalogInputPin.h"

AnalogInputPin::AnalogInputPin(InputPinConfig&& pin_config, HwApi& hw_api) : hw_api{hw_api}, config{pin_config} {
}

void AnalogInputPin::begin() {
    hw_api.pinMode(config.getPin(), config.isPullup() ? HwApi::PIN_MODE::INPUT_PULLUP_MODE : HwApi::PIN_MODE::INPUT_MODE);
}

void AnalogInputPin::loop() {
    read();
}

int AnalogInputPin::read() {
    current_value = hw_api.analogRead(config.getPin());
    return current_value;
}

int AnalogInputPin::getValue() const {
    return current_value;
}
