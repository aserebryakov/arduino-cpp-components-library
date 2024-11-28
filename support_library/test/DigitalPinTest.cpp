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

#include "../src/DigitalPin.h"

using namespace ::testing;

class DigitalPinTest : public Test {
protected:
    NiceMock<HwApiMock> hwApiMock{};

    static void onLowHighChange(void* self) {
        (static_cast<DigitalPinTest*>(self)->on_low_high_calls)++;
    }

    static void onHighLowChange(void* self) {
        (static_cast<DigitalPinTest*>(self)->on_high_low_calls)++;
    }

    int on_low_high_calls{0};
    int on_high_low_calls{0};
};

TEST_F(DigitalPinTest, Construction) {
    DigitalPin pin{0, HwApi::PIN_MODE::INPUT_PULLUP_MODE, hwApiMock};
    EXPECT_EQ(pin.getLevel(), HwApi::LEVEL_HIGH);
    EXPECT_EQ(pin.getPinChange(), PIN_CHANGE::NONE);
}

TEST_F(DigitalPinTest, ReadTest) {
    EXPECT_CALL(hwApiMock, digitalRead(42)).Times(3)
        .WillOnce(Return(HwApi::LEVEL_LOW))
        .WillOnce(Return(HwApi::LEVEL_LOW))
        .WillOnce(Return(HwApi::LEVEL_HIGH));

    DigitalPin pin{42, HwApi::PIN_MODE::INPUT_PULLUP_MODE, hwApiMock};
    EXPECT_EQ(pin.read(), HwApi::LEVEL_LOW);
    EXPECT_EQ(pin.getLevel(), HwApi::LEVEL_LOW);
    EXPECT_EQ(pin.getPinChange(), PIN_CHANGE::HIGH_LOW);

    EXPECT_EQ(pin.read(), HwApi::LEVEL_LOW);
    EXPECT_EQ(pin.getLevel(), HwApi::LEVEL_LOW);
    EXPECT_EQ(pin.getPinChange(), PIN_CHANGE::NONE);

    EXPECT_EQ(pin.read(), HwApi::LEVEL_HIGH);
    EXPECT_EQ(pin.getLevel(), HwApi::LEVEL_HIGH);
    EXPECT_EQ(pin.getPinChange(), PIN_CHANGE::LOW_HIGH);
}

TEST_F(DigitalPinTest, CallbackTest) {
    EXPECT_CALL(hwApiMock, pinMode(42, HwApi::PIN_MODE::INPUT_PULLUP_MODE)).Times(1);

    EXPECT_CALL(hwApiMock, digitalRead(42)).Times(3)
        .WillOnce(Return(HwApi::LEVEL_LOW))
        .WillOnce(Return(HwApi::LEVEL_LOW))
        .WillOnce(Return(HwApi::LEVEL_HIGH));

    DigitalPin pin{
        42, HwApi::PIN_MODE::INPUT_PULLUP_MODE,
        {onLowHighChange,this},
        {onHighLowChange, this},
        hwApiMock
    };

    pin.setup();

    pin.loop();
    EXPECT_EQ(on_high_low_calls, 1);
    EXPECT_EQ(on_low_high_calls, 0);

    pin.loop();
    EXPECT_EQ(on_high_low_calls, 1);
    EXPECT_EQ(on_low_high_calls, 0);

    pin.loop();
    EXPECT_EQ(on_high_low_calls, 1);
    EXPECT_EQ(on_low_high_calls, 1);
}
