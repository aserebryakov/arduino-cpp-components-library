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
#include "HwApiMock.h"

#include "../GenericController.h"
#include "../RotaryEncoder.h"
#include "../HeapObject.h"

using namespace utility;

class TestControl : public Control {
public:
    TestControl(HwApi& hw_api) : Control(hw_api) {
    }

    virtual ~TestControl() override = default;

    virtual void setup() override {

    }

    virtual void loop() override {

    }
};

TEST(ControllerBuilderTest, Construction) {
    HwApiMock hw_api_mock{};

    GenericController<Control, 2> builder{
        HeapObject<Control>(new TestControl(hw_api_mock)),
        HeapObject<Control>(new TestControl(hw_api_mock))
    };
}
