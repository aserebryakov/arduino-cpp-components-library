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

#ifndef HWAPI_H
#define HWAPI_H

#include <stdint.h> // Using C header for compatibility

class HwApi {
public:
    enum DIGITAL_PIN_LEVEL : int {
        LEVEL_HIGH = 0x1,
        LEVEL_LOW = 0x0
    };

    enum class PIN_MODE : int {
        INPUT_MODE = 0x0,
        OUTPUT_MODE = 0x1,
        INPUT_PULLUP_MODE = 0x2
    };

    virtual ~HwApi() = default;

    virtual void digitalWrite(const uint8_t pin, const uint8_t val) const = 0;
    virtual int digitalRead(const uint8_t pin) const = 0;
    virtual void pinMode(const uint8_t pin, const PIN_MODE mode) const = 0;
};


#endif //HWAPI_H
