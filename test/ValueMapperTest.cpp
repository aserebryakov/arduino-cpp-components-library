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

#include <gtest/gtest.h>
#include "ValueMapper.h"

TEST(ValueMapperTest, LinearMapping) {
    ValueMapper mapper{0, 1023, 0, 255};
    
    EXPECT_EQ(mapper.map(0), 0);
    EXPECT_EQ(mapper.map(1023), 255);
    EXPECT_EQ(mapper.map(511), 127); // (511 - 0) * 255 / 1023 = 127.24
}

TEST(ValueMapperTest, InverseMapping) {
    ValueMapper mapper{0, 1023, 255, 0};
    
    EXPECT_EQ(mapper.map(0), 255);
    EXPECT_EQ(mapper.map(1023), 0);
    EXPECT_EQ(mapper.map(511), 128); // 255 + (511 - 0) * (0 - 255) / 1023 = 255 - 127.24 = 127.76 -> 127 or 128?
}

TEST(ValueMapperTest, SmallRangeMapping) {
    ValueMapper mapper{0, 10, 0, 100};
    
    EXPECT_EQ(mapper.map(0), 0);
    EXPECT_EQ(mapper.map(5), 50);
    EXPECT_EQ(mapper.map(10), 100);
}

TEST(ValueMapperTest, NegativeValues) {
    ValueMapper mapper{-100, 100, 0, 1000};
    
    EXPECT_EQ(mapper.map(-100), 0);
    EXPECT_EQ(mapper.map(0), 500);
    EXPECT_EQ(mapper.map(100), 1000);
}

TEST(ValueMapperTest, ZeroInputRange) {
    ValueMapper mapper{10, 10, 0, 100};
    EXPECT_EQ(mapper.map(10), 0);
    EXPECT_EQ(mapper.map(20), 0);
}
