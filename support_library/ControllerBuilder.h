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

#ifndef CONTROLLERBUILDER_H
#define CONTROLLERBUILDER_H

#include <cstddef>

#include "HwApi.h"
#include "HeapObject.h"

class Control {
public:
    Control() = default;
    Control(HwApi& hw_api) : hw_api(&hw_api) {};

private:
    HwApi* hw_api{nullptr};
};

template<typename First, typename... Rest>
void setValue(const size_t index, utility::HeapObject<Control> storage[], First&& first, Rest&&... rest) {
    storage[index] = static_cast<utility::HeapObject<Control>&&>(first); // effectively replaces std::move but not 100% correct
    setValue(index + 1, storage, rest...);
}

void setValue(const size_t index, utility::HeapObject<Control> storage[]) {
}

template <typename T, size_t NumberOfControls>
class ControllerBuilder {
public:
    template <typename... Args>
    ControllerBuilder(Args&& ...args) {
        static_assert((sizeof...(Args)) == NumberOfControls, "Wrong number of controls");
        setValue(0, controls, args...);
    }

    utility::HeapObject<T> controls[NumberOfControls];
};


#endif //CONTROLLERBUILDER_H
