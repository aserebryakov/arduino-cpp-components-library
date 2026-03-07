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

// This example demonstrates how to work with Potentiometer object.
//
// Hardware:
// - Arduino
// - Potentiometer connected to A0
//
// Setup:
// - Potentiometer center pin is connected to A0
// - Other pins are connected to 5V and GND

#include <Arduino.h>
#include <CppComponentsLibrary.h>

// Instantiate a hardware api object.
HwApiImpl hw_api{};

// Define mapping for Potentiometer: 10-bit ADC (0-1023) to percentage (0-100)
ValueMapper potMapper{0, 1023, 0, 100};

// Instantiate analog input on A0
AnalogInput pot{{A0, false}, hw_api, potMapper};

void setup() {
    Serial.begin(9600);
    pot.begin(); // Initialization (includes pin configuration)
}

void loop() {
    pot.loop(); // Refresh the internal state

    int rawValue = pot.getRawValue();
    int mappedValue = pot.getMappedValue();

    Serial.print("Raw: ");
    Serial.print(rawValue);
    Serial.print(" | Mapped: ");
    Serial.print(mappedValue);
    Serial.println("%");

    delay(100);
}
