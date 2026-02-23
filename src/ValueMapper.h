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

#ifndef VALUEMAPPER_H
#define VALUEMAPPER_H

/**
 * Utility class to map values from a source range to a target range.
 */
class ValueMapper {
public:
    /**
     * Constructor.
     * 
     * @param[in] in_min Lower bound of the source range
     * @param[in] in_max Upper bound of the source range
     * @param[in] out_min Lower bound of the target range
     * @param[in] out_max Upper bound of the target range
     */
    ValueMapper(const int in_min, const int in_max, const int out_min, const int out_max)
        : in_min{in_min}, in_max{in_max}, out_min{out_min}, out_max{out_max} {}

    /**
     * Maps a value based on the pre-configured source and target ranges.
     * 
     * @param[in] value The value to be mapped (using long because int * int overflows)
     * @return The mapped value
     */
    int map(const long value) const {
        if (in_max == in_min) return out_min;
        return static_cast<int>((value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
    }

private:
    int in_min;
    int in_max;
    int out_min;
    int out_max;
};

#endif // VALUEMAPPER_H
