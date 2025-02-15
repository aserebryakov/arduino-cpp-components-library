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

#include <stddef.h>

#include "HeapObject.h"
#include "Component.h"
#include "Utilities.h"

template <typename First, typename... Rest>
void setValue(const size_t index, utility::HeapObject<Component> storage[], First&& first, Rest&&... rest) {
    storage[index] = utilities::move(first);
    setValue(index + 1, storage, rest...);
}

template <typename Last>
void setValue(const size_t index, utility::HeapObject<Component> storage[], Last&& last) {
    storage[index] = utilities::move(last);
}

template <size_t NumberOfComponents>
class ComponentsComposition {
public:
    template <typename... Args>
    ComponentsComposition(Args&&... args) {
        static_assert((sizeof...(Args)) == NumberOfComponents, "Wrong number of hardware devices");
        setValue(0, devices, args...);
    }

    void begin() {
        for (auto& device : devices) {
            device->begin();
        }
    }

    void loop() {
        for (auto& device : devices) {
            device->loop();
        }
    }

private:
    utility::HeapObject<Component> devices[NumberOfComponents];
};


#endif //CONTROLLERBUILDER_H
