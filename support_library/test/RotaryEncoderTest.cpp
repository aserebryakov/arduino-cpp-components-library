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
    DigitalPin dt_pin{DT_PIN, hw_api_mock};
    DigitalPin clk_pin{CLK_PIN, hw_api_mock};
    DigitalPin sw_pin{SW_PIN, hw_api_mock};
};

TEST_F(RotaryEncoderTest, Constuction) {
    RotaryEncoder encoder{DT_PIN, CLK_PIN, SW_PIN, hw_api_mock};
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
    EXPECT_CALL(hw_api_mock, digitalRead(DT_PIN)).Times(2).WillOnce(Return(HwApi::LEVEL_LOW)).WillOnce(Return(HwApi::LEVEL_HIGH));
    EXPECT_CALL(hw_api_mock, digitalRead(CLK_PIN)).Times(2).WillRepeatedly(Return(HwApi::LEVEL_LOW));

    RotaryEncoder encoder{DT_PIN, CLK_PIN, SW_PIN, hw_api_mock};

    TestCallback callback{};
    encoder.setTurnClockwiseCallback({TestCallback::callback, &callback});
    encoder.readPins(); // To read level drop
    encoder.readPins();

    EXPECT_EQ(1, callback.calls_count);
}

TEST_F(RotaryEncoderTest, OnTurnCounterClockwiseTest) {
    EXPECT_CALL(hw_api_mock, digitalRead(testing::_)).Times(AnyNumber());
    EXPECT_CALL(hw_api_mock, digitalRead(DT_PIN)).Times(2).WillOnce(Return(HwApi::LEVEL_LOW)).WillOnce(Return(HwApi::LEVEL_HIGH));
    EXPECT_CALL(hw_api_mock, digitalRead(CLK_PIN)).Times(2).WillRepeatedly(Return(HwApi::LEVEL_HIGH));

    RotaryEncoder encoder{DT_PIN, CLK_PIN, SW_PIN, hw_api_mock};

    TestCallback callback{};
    encoder.setTurnCounterClockwiseCallback({TestCallback::callback, &callback});
    encoder.readPins(); // To read level drop
    encoder.readPins();

    EXPECT_EQ(1, callback.calls_count);
}

TEST_F(RotaryEncoderTest, OnPushButtonTest) {
    EXPECT_CALL(hw_api_mock, digitalRead(testing::_)).Times(AnyNumber());
    EXPECT_CALL(hw_api_mock, digitalRead(SW_PIN)).Times(2).WillRepeatedly(Return(HwApi::LEVEL_LOW));

    RotaryEncoder encoder{DT_PIN, CLK_PIN, SW_PIN, hw_api_mock};

    TestCallback callback{};
    encoder.setPushButtonCallback({TestCallback::callback, &callback});
    encoder.readPins(); // To read level drop
    encoder.readPins();

    EXPECT_EQ(1, callback.calls_count);
}