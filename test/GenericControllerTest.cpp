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

#include <Component.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "HwApiMock.h"

#include "ComponentsComposition.h"
#include "HeapObject.h"

using namespace utility;

class TestControl1 : public Component {
public:
    TestControl1(HwApi& hw_api) : hw_api(hw_api) {
    }

    virtual ~TestControl1() override = default;

    virtual void begin() override {
        hw_api.digitalRead(1);
    }

    virtual void loop() override {
        hw_api.digitalWrite(1, 1);
    }

private:
    HwApi& hw_api;
};

class TestControl2 : public Component {
public:
    TestControl2(HwApi& hw_api) : hw_api(hw_api) {
    }

    virtual ~TestControl2() override = default;

    virtual void begin() override {
        hw_api.digitalRead(2);
    }

    virtual void loop() override {
        hw_api.digitalWrite(2, 2);
    }

private:
    HwApi& hw_api;
};

TEST(GeneticControllerTest, Construction) {
    HwApiMock hw_api_mock{};

    ComponentsComposition<2> controller{
        HeapObject<Component>(new TestControl1(hw_api_mock)),
        HeapObject<Component>(new TestControl2(hw_api_mock))
    };
}

TEST(GeneticControllerTest, SetupTest) {
    HwApiMock hw_api_mock{};
    EXPECT_CALL(hw_api_mock, digitalRead(1)).Times(1);
    EXPECT_CALL(hw_api_mock, digitalRead(2)).Times(1);

    ComponentsComposition<2> controller{
        HeapObject<Component>(new TestControl1(hw_api_mock)),
        HeapObject<Component>(new TestControl2(hw_api_mock))
    };

    controller.begin();
}

TEST(GeneticControllerTest, LoopTest) {
    HwApiMock hw_api_mock{};
    EXPECT_CALL(hw_api_mock, digitalWrite(1, 1)).Times(1);
    EXPECT_CALL(hw_api_mock, digitalWrite(2, 2)).Times(1);

    ComponentsComposition<2> controller{
        HeapObject<Component>(new TestControl1(hw_api_mock)),
        HeapObject<Component>(new TestControl2(hw_api_mock))
    };

    controller.loop();
}
