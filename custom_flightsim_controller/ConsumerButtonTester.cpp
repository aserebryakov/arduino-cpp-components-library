
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

#include "ConsumerButtonTester.h"
#include <Arduino.h>
#include "HID-Project.h"

ConsumerButtonTester::ConsumerButtonTester(const int dt_pin, const int clk_pin, const int sw_pin, HwApi& hw_api) :
  encoder{
    {dt_pin, true},
    {clk_pin, true},
    {sw_pin, true},
    hw_api,
    {nextButton, this},
    {previousButton, this},
    {press, this}
  }
{
}

inline void ConsumerButtonTester::begin() {
    Consumer.begin();
    encoder.begin();
}

inline void ConsumerButtonTester::loop() {
    encoder.loop();
}

inline void ConsumerButtonTester::nextButton(void* self) {
    (static_cast<ConsumerButtonTester*>(self)->button_code)++;
    Serial.println(static_cast<ConsumerButtonTester*>(self)->button_code, HEX);
}

inline void ConsumerButtonTester::previousButton(void* self) {
    (static_cast<ConsumerButtonTester*>(self)->button_code)--;
    Serial.println(static_cast<ConsumerButtonTester*>(self)->button_code, HEX);
}

inline void ConsumerButtonTester::press(void* self) {
    Consumer.write(static_cast<ConsumerKeycode>((static_cast<ConsumerButtonTester*>(self)->button_code)));
    Serial.println(static_cast<ConsumerButtonTester*>(self)->button_code, HEX);
}