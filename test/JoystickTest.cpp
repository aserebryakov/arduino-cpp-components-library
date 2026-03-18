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

#include "Joystick.h"
#include "HwApiMock.h"

using namespace ::testing;

constexpr auto X_PIN{1};
constexpr auto Y_PIN{2};
constexpr auto SW_PIN{3};

class TestCallback {
public:
    static void callback(void* context) {
        static_cast<TestCallback*>(context)->calls_count++;
    }

    int calls_count{0};
};

class JoystickTest : public Test {
protected:
    NiceMock<HwApiMock> hw_api_mock{};
};

TEST_F(JoystickTest, Construction) {
    Joystick joystick{
        {{X_PIN, false}, hw_api_mock},
        {{Y_PIN, false}, hw_api_mock},
        {{SW_PIN, false}, hw_api_mock}
    };
}

TEST_F(JoystickTest, SetupTest) {
    EXPECT_CALL(hw_api_mock, pinMode(X_PIN, HwApi::PIN_MODE::INPUT_MODE)).Times(1);
    EXPECT_CALL(hw_api_mock, pinMode(Y_PIN, HwApi::PIN_MODE::INPUT_MODE)).Times(1);
    EXPECT_CALL(hw_api_mock, pinMode(SW_PIN, HwApi::PIN_MODE::INPUT_MODE)).Times(1);

    Joystick joystick{
        {{X_PIN, false}, hw_api_mock},
        {{Y_PIN, false}, hw_api_mock},
        {{SW_PIN, false}, hw_api_mock}
    };

    joystick.begin();
}

TEST_F(JoystickTest, GetValuesTest) {
    EXPECT_CALL(hw_api_mock, analogRead(X_PIN)).WillOnce(Return(512));
    EXPECT_CALL(hw_api_mock, analogRead(Y_PIN)).WillOnce(Return(512));

    Joystick joystick{
        {{X_PIN, false}, hw_api_mock, {0, 1023, 0, 511}},
        {{Y_PIN, false}, hw_api_mock},
        {{SW_PIN, false}, hw_api_mock}
    };

    joystick.loop();

    EXPECT_EQ(512, joystick.getXRaw());
    EXPECT_EQ(255, joystick.getX());
    EXPECT_EQ(512, joystick.getYRaw());
    EXPECT_EQ(512, joystick.getY());
}

TEST_F(JoystickTest, OnPushOnReleaseTest) {
    EXPECT_CALL(hw_api_mock, digitalRead(SW_PIN))
        .WillOnce(Return(HwApi::LEVEL_LOW))
        .WillOnce(Return(HwApi::LEVEL_HIGH));

    TestCallback callback{};

    Joystick joystick{
        {{X_PIN, false}, hw_api_mock},
        {{Y_PIN, false}, hw_api_mock},
        {{SW_PIN, true}, hw_api_mock, {TestCallback::callback, &callback}, {TestCallback::callback, &callback}}
    };

    joystick.loop();
    EXPECT_EQ(callback.calls_count, 1);

    joystick.loop();
    EXPECT_EQ(callback.calls_count, 2);
}
