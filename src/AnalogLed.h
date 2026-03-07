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

#ifndef ANALOGLED_H
#define ANALOGLED_H

#include "Component.h"
#include "AnalogOutputPin.h"

/**
 * Represents abstraction level for analog LED (PWM).
 */
class AnalogLed : public Component {
public:
    /**
      * Constructor.
      *
      * @param[in] pin_number Pin number
      * @param[in] hw_api Hardware API implementation reference
      */
    AnalogLed(const int pin_number, HwApi& hw_api);
    virtual ~AnalogLed() override = default;

    void begin() override;
    void loop() override;

    /**
     * Turns LED on (maximum brightness).
     */
    void turnOn() const;

    /**
     * Turns LED off.
     */
    void turnOff() const;

    /**
     * Sets LED brightness.
     *
     * @param[in] value the duty cycle: between 0 (always off) and 255 (always on).
     */
    void setBrightness(const int value) const;

private:
    AnalogOutputPin pin;
};

#endif //ANALOGLED_H
