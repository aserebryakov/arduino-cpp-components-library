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

using namespace ::testing;

class MockPin : public RotaryEncoderPin {
public:
    MOCK_METHOD(PIN_CHANGE, readPinChange, (), (override));
    MOCK_METHOD(bool, readPinStatus, (), (override));
};

TEST(RotaryEncoderTest, Constuction) {
    MockPin dt_pin{};
    MockPin clk_pin{};
    MockPin sw_pin{};

    RotaryEncoder encoder{dt_pin, clk_pin, sw_pin};
}

class TestCallback {
public:
    static void callback(void* context) {
        static_cast<TestCallback*>(context)->calls_count++;
    }

    int calls_count{0};
};

TEST(RotaryEncoderTest, OnTurnClockwiseTest) {
    MockPin dt_pin{};
    MockPin clk_pin{};
    MockPin sw_pin{};

    EXPECT_CALL(dt_pin, readPinChange()).Times(1).WillOnce(Return(PIN_CHANGE::LOW_HIGH));
    EXPECT_CALL(clk_pin, readPinStatus()).Times(1).WillOnce(Return(false));

    RotaryEncoder encoder{dt_pin, clk_pin, sw_pin};

    TestCallback on_turn_clockwise{};
    encoder.setTurnClockwiseCallback({TestCallback::callback, &on_turn_clockwise});
    encoder.readStatus();

    EXPECT_EQ(1, on_turn_clockwise.calls_count);
}