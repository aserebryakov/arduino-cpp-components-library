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
#include "../HeapObject.h"

using namespace utility;

class TestObject {
public:
    int value{42};
};

TEST(HeapObjectTest, AllocateOperatorsDeallocate) {
    const auto object{makeHeapObject<TestObject>()};
    EXPECT_EQ((*object).value, 42);
    (*object).value = 43;
    EXPECT_EQ(object->value, 43);
}

TEST(HeapObjectTest, MoveAssignment) {
    auto object{makeHeapObject<TestObject>()};
    object->value = 43;
    ASSERT_EQ(object->value, 43);

    object = makeHeapObject<TestObject>();
    EXPECT_EQ(object->value, 42);
}

TEST(HeapObjectTest, MoveConstructor) {
    auto object{makeHeapObject<TestObject>()};

    HeapObject<TestObject> object2{std::move(object)};
}