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

#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <utility>

#include "Component.h"
#include "AnalogInput.h"
#include "Button.h"
#include "Callback.h"
#include "Utilities.h"
#include "ValueMapper.h"

/**
 * Implements joystick functionality.
 */
class Joystick : public Component {
public:
    /**
     * Constructur.
     *
     * @param x_input X input
     * @param y_input Y input
     * @param button Button
     */
    Joystick(AnalogInput&& x_input,
             AnalogInput&& y_input,
             Button&& button);

    virtual ~Joystick() override = default;

    /**
     * Reads the raw analog values of the joystick.
     */
    int getXRaw() const;
    int getYRaw() const;

    /**
     * Returns the mapped values of the joystick.
     */
    int getX() const;
    int getY() const;

    void begin() override;
    void loop() override;

private:
    AnalogInput x_input;
    AnalogInput y_input;
    Button button;
};

#endif //JOYSTICK_H
