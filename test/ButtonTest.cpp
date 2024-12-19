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

#include "Button.h"

using namespace ::testing;

class ButtonTest : public Test {
protected:
    NiceMock<HwApiMock> hwApiMock{};

    static void onPress(void* self) {
        (static_cast<ButtonTest*>(self)->on_press_calls)++;
    }

    static void onRelease(void* self) {
        (static_cast<ButtonTest*>(self)->on_release_calls)++;
    }

    int on_press_calls{0};
    int on_release_calls{0};
};

TEST_F(ButtonTest, OnPressTest) {
    EXPECT_CALL(hwApiMock, pinMode(42, HwApi::PIN_MODE::INPUT_PULLUP_MODE)).Times(1);

    EXPECT_CALL(hwApiMock, digitalRead(42)).Times(3)
        .WillOnce(Return(HwApi::LEVEL_LOW))
        .WillOnce(Return(HwApi::LEVEL_LOW))
        .WillOnce(Return(HwApi::LEVEL_HIGH));

    Button button{
        {42, true},
        hwApiMock,
        {onPress, this},
        {onRelease, this}
    };

    button.begin();

    button.loop();
    EXPECT_EQ(on_press_calls, 1);
    EXPECT_EQ(on_release_calls, 0);

    button.loop();
    EXPECT_EQ(on_press_calls, 1);
    EXPECT_EQ(on_release_calls, 0);

    button.loop();
    EXPECT_EQ(on_press_calls, 1);
    EXPECT_EQ(on_release_calls, 1);
}
