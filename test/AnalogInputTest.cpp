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

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "HwApiMock.h"

#include "AnalogInput.h"

using namespace ::testing;

class AnalogInputTest : public Test {
protected:
    NiceMock<HwApiMock> hwApiMock{};
    const int PIN_NUMBER = 14;
    const ValueMapper defaultMapper{0, 1023, 0, 100};
};

TEST_F(AnalogInputTest, InitialValues) {
    AnalogInput pot{{PIN_NUMBER, false}, hwApiMock, defaultMapper};
    EXPECT_EQ(pot.getRawValue(), 0);
    EXPECT_EQ(pot.getMappedValue(), 0);
}

TEST_F(AnalogInputTest, InitializationAndLoop) {
    EXPECT_CALL(hwApiMock, pinMode(PIN_NUMBER, HwApi::PIN_MODE::INPUT_MODE)).Times(1);
    EXPECT_CALL(hwApiMock, analogRead(PIN_NUMBER)).WillRepeatedly(Return(511));

    AnalogInput pot{{PIN_NUMBER, false}, hwApiMock, defaultMapper};
    pot.begin();
    pot.loop();

    EXPECT_EQ(pot.getRawValue(), 511);
    EXPECT_EQ(pot.getMappedValue(), 49); // (511 - 0) * 100 / 1023 = 49.95
}

TEST_F(AnalogInputTest, ValueUpdates) {
    AnalogInput pot{{PIN_NUMBER, false}, hwApiMock, defaultMapper};
    
    EXPECT_CALL(hwApiMock, analogRead(PIN_NUMBER))
        .WillOnce(Return(0))
        .WillOnce(Return(1023))
        .WillOnce(Return(511));

    pot.loop();
    EXPECT_EQ(pot.getRawValue(), 0);
    EXPECT_EQ(pot.getMappedValue(), 0);

    pot.loop();
    EXPECT_EQ(pot.getRawValue(), 1023);
    EXPECT_EQ(pot.getMappedValue(), 100);

    pot.loop();
    EXPECT_EQ(pot.getRawValue(), 511);
    EXPECT_EQ(pot.getMappedValue(), 49);
}
