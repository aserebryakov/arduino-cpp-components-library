
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

#include "HwApiImpl.h"

#include "Arduino.h"

void HwApiImpl::digitalWrite(const uint8_t pin, const uint8_t val) const {
    ::digitalWrite(pin, val);
}

int HwApiImpl::digitalRead(const uint8_t pin) const {
    return ::digitalRead(pin);
}

void HwApiImpl::pinMode(const uint8_t pin, const PIN_MODE mode) const {
    static_assert(static_cast<int>(PIN_MODE::INPUT_MODE) == INPUT);
    static_assert(static_cast<int>(PIN_MODE::OUTPUT_MODE) == OUTPUT);
    static_assert(static_cast<int>(PIN_MODE::INPUT_PULLUP_MODE) == INPUT_PULLUP);

    ::pinMode(pin, static_cast<int>(mode));
}
