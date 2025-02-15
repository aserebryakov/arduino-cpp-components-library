// MIT License
//
// Copyright (c) 2025 Alexander Serebryakov
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

// This example demonstrates how to work with DigitalLed object.
//
// Hardware:
// - Arduino
// - LED
//
// Setup:
// - LED is connected to D2

#include <Arduino.h>
#include <CppComponentsLibrary.h>

// Instantiate a hardware api object.
HwApiImpl hw_api{};

constexpr int LED_PIN{2};

DigitalLed led{
  LED_PIN, // Set LED pin number
  hw_api // provide the instance of HwApi to control pin
  };

void setup() {
  led.begin(); // Initialization (includes pin configuration)
}

void loop() {
  led.turnOn(); // Turns LED on
  delay(500);
  led.turnOff(); // Turns LED off
  delay(500);
}

