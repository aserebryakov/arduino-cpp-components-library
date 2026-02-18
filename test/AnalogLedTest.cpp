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

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "HwApiMock.h"

#include "AnalogLed.h"

using namespace ::testing;

class AnalogLedTest : public Test {
protected:
    NiceMock<HwApiMock> hw_api_mock{};
};

TEST_F(AnalogLedTest, Begin) {
    EXPECT_CALL(hw_api_mock, pinMode(42, HwApi::PIN_MODE::OUTPUT_MODE)).Times(1);
    AnalogLed led{42, hw_api_mock};
    led.begin();
}

TEST_F(AnalogLedTest, TurnOn) {
    EXPECT_CALL(hw_api_mock, analogWrite(42, 255)).Times(1);
    AnalogLed led{42, hw_api_mock};
    led.turnOn();
}

TEST_F(AnalogLedTest, TurnOff) {
    EXPECT_CALL(hw_api_mock, analogWrite(42, 0)).Times(1);
    AnalogLed led{42, hw_api_mock};
    led.turnOff();
}

TEST_F(AnalogLedTest, SetBrightness) {
    EXPECT_CALL(hw_api_mock, analogWrite(42, 128)).Times(1);
    AnalogLed led{42, hw_api_mock};
    led.setBrightness(128);
}
