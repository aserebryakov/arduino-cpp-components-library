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

#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include "Component.h"
#include "AnalogInputPin.h"
#include "ValueMapper.h"

/**
 * Represents an analog input component with mapping support.
 */
class AnalogInput : public Component {
public:
    /**
     * Constructor.
     * 
     * @param[in] config Pin configuration
     * @param[in] hw_api Reference to Hardware API
     * @param[in] mapper ValueMapper instance used for scaling readings
     */
    AnalogInput(InputPinConfig&& config,
                  HwApi& hw_api, 
                  const ValueMapper& mapper);

    virtual ~AnalogInput() override = default;

    /**
     * Initializes the underlying pin hardware.
     */
    virtual void begin() override;

    /**
     * Refreshes the internal pin state.
     */
    virtual void loop() override;

    /**
     * Returns the raw analog value (typically 0-1023).
     */
    int getRawValue() const;

    /**
     * Returns the value scaled by the internal ValueMapper.
     */
    int getMappedValue() const;

private:
    AnalogInputPin pin;
    ValueMapper mapper;
};

#endif // POTENTIOMETER_H
