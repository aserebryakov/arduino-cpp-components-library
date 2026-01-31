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

#include "AnalogInputPin.h"

using namespace ::testing;

class AnalogInputPinTest : public Test {
protected:
    NiceMock<HwApiMock> hwApiMock{};
};

TEST_F(AnalogInputPinTest, Construction) {
    AnalogInputPin pin{{14, false}, hwApiMock};
    EXPECT_EQ(pin.getValue(), 0);
}

TEST_F(AnalogInputPinTest, ReadTest) {
    EXPECT_CALL(hwApiMock, analogRead(14)).Times(3)
        .WillOnce(Return(100))
        .WillOnce(Return(200))
        .WillOnce(Return(300));

    AnalogInputPin pin{{14, false}, hwApiMock};
    EXPECT_EQ(pin.read(), 100);
    EXPECT_EQ(pin.getValue(), 100);

    EXPECT_EQ(pin.read(), 200);
    EXPECT_EQ(pin.getValue(), 200);

    EXPECT_EQ(pin.read(), 300);
    EXPECT_EQ(pin.getValue(), 300);
}

TEST_F(AnalogInputPinTest, BeginAndLoop) {
    EXPECT_CALL(hwApiMock, pinMode(14, HwApi::PIN_MODE::INPUT_MODE)).Times(1);
    EXPECT_CALL(hwApiMock, analogRead(14)).Times(1).WillOnce(Return(512));

    AnalogInputPin pin{{14, false}, hwApiMock};
    pin.begin();
    pin.loop();

    EXPECT_EQ(pin.getValue(), 512);
}
