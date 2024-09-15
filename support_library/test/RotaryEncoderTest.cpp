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

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../RotaryEncoder.h"
#include "HwApiMock.h"

using namespace ::testing;

constexpr auto DT_PIN{1};
constexpr auto CLK_PIN{2};
constexpr auto SW_PIN{3};

class RotaryEncoderTest : public Test {
protected:
    NiceMock<HwApiMock> hw_api_mock{};
    RotaryEncoderPin dt_pin{DT_PIN, hw_api_mock};
    RotaryEncoderPin clk_pin{CLK_PIN, hw_api_mock};
    RotaryEncoderPin sw_pin{SW_PIN, hw_api_mock};
};

TEST_F(RotaryEncoderTest, Constuction) {
    RotaryEncoder encoder{dt_pin, clk_pin, sw_pin};
}

class TestCallback {
public:
    static void callback(void* context) {
        static_cast<TestCallback*>(context)->calls_count++;
    }

    int calls_count{0};
};

TEST_F(RotaryEncoderTest, OnTurnClockwiseTest) {
    EXPECT_CALL(hw_api_mock, digitalRead(testing::_)).Times(AnyNumber());
    EXPECT_CALL(hw_api_mock, digitalRead(DT_PIN)).Times(1).WillOnce(Return(HwApi::PIN_HIGH));
    EXPECT_CALL(hw_api_mock, digitalRead(CLK_PIN)).Times(1).WillOnce(Return(HwApi::PIN_LOW));

    RotaryEncoder encoder{dt_pin, clk_pin, sw_pin};

    TestCallback callback{};
    encoder.setTurnClockwiseCallback({TestCallback::callback, &callback});
    encoder.readStatus();

    EXPECT_EQ(1, callback.calls_count);
}

TEST_F(RotaryEncoderTest, OnTurnCounterClockwiseTest) {
    EXPECT_CALL(hw_api_mock, digitalRead(testing::_)).Times(AnyNumber());
    EXPECT_CALL(hw_api_mock, digitalRead(DT_PIN)).Times(1).WillOnce(Return(HwApi::PIN_HIGH));
    EXPECT_CALL(hw_api_mock, digitalRead(CLK_PIN)).Times(1).WillOnce(Return(HwApi::PIN_HIGH));

    RotaryEncoder encoder{dt_pin, clk_pin, sw_pin};

    TestCallback callback{};
    encoder.setTurnCounterClockwiseCallback({TestCallback::callback, &callback});
    encoder.readStatus();

    EXPECT_EQ(1, callback.calls_count);
}

TEST_F(RotaryEncoderTest, OnPushButtonTest) {
    EXPECT_CALL(hw_api_mock, digitalRead(testing::_)).Times(AnyNumber());
    EXPECT_CALL(hw_api_mock, digitalRead(SW_PIN)).Times(1).WillOnce(Return(HwApi::PIN_HIGH));

    RotaryEncoder encoder{dt_pin, clk_pin, sw_pin};

    TestCallback callback{};
    encoder.setPushButtonCallback({TestCallback::callback, &callback});
    encoder.readStatus();

    EXPECT_EQ(1, callback.calls_count);
}