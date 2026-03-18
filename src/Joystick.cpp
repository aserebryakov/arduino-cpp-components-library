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

#include "Joystick.h"
#include "Utilities.h"


Joystick::Joystick(AnalogInput &&x_input, AnalogInput &&y_input, Button &&button)
    : x_input(utilities::move(x_input)),
      y_input(utilities::move(y_input)),
      button(utilities::move(button)) {
}

int Joystick::getXRaw() const {
    return x_input.getRawValue();
}

int Joystick::getYRaw() const {
    return y_input.getRawValue();
}

int Joystick::getX() const {
    return x_input.getMappedValue();
}

int Joystick::getY() const {
    return y_input.getMappedValue();
}

void Joystick::begin() {
    x_input.begin();
    y_input.begin();
    button.begin();
}

void Joystick::loop() {
    x_input.loop();
    y_input.loop();
    button.loop();
}
