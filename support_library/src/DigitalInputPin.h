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

#ifndef DIGITALINPUTPINIMPL_H
#define DIGITALINPUTPINIMPL_H

#include "HwApi.h"
#include "Callback.h"
#include "Pin.h"
#include "InputPinConfig.h"

enum class PIN_CHANGE {
    LOW_HIGH,
    HIGH_LOW,
    NONE
};

/**
 * Represents abstraction level for digital pin.
 */
class DigitalInputPin : public Pin {
public:
    /**
      * Constructor.
      *
      * @param[in] pin_config Pin configuration
      * @param[in] hw_api Hardware API implementation reference
      */
    DigitalInputPin(InputPinConfig&& pin_config, HwApi& hw_api);

    /**
     * Constructor.
     *
     * @param[in] pin_config Pin configuration
     * @param[in] on_low_high_change Callback for change from LOW to HIGH
     * @param[in] on_high_low_change Callback for change from HIGH to LOW
     * @param[in] hw_api Hardware API implementation reference
     */
    DigitalInputPin(InputPinConfig&& pin_config, Callback&& on_low_high_change,
               Callback&& on_high_low_change, HwApi& hw_api);

    virtual ~DigitalInputPin() override = default;

    /**
     * Reads the level of the pin.
     *
     * Updates internal states (pin change and current level).
     *
     * @return pin level.
     */
    HwApi::DIGITAL_PIN_LEVEL read();

    /**
     * Returns previously read pin level.
     *
     * @return pin level
     */
    HwApi::DIGITAL_PIN_LEVEL getLevel() const;

    /**
     * Returns level change between last two reads.
     *
     * @return level change (low-high or high-low)
     */
    PIN_CHANGE getPinChange() const;

    void begin() override;
    void loop() override;

private:
    HwApi& hw_api;
    InputPinConfig config;
    Callback on_low_high_change_callback;
    Callback on_high_low_change_callback;
    HwApi::DIGITAL_PIN_LEVEL current_level{HwApi::LEVEL_HIGH};
    HwApi::DIGITAL_PIN_LEVEL previous_level{HwApi::LEVEL_HIGH};
};

#endif //DIGITALINPUTPINIMPL_H
