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

#include "GameController.h"

using utility::HeapObject;

GameController::GameController(HwApi& hw_api) : components{
    HeapObject<Component>(new ControllerRotaryEncoder(21, 20, 19, 1, 2, 3, hw_api)),
    HeapObject<Component>(new ControllerRotaryEncoder(18, 15, 14, 4, 5, 6, hw_api)),
    HeapObject<Component>(new ControllerRotaryEncoder(16, 10, 9, 7, 8, 9, hw_api)),
    HeapObject<Component>(new ControllerButton(0, 10, hw_api)),
    HeapObject<Component>(new ControllerButton(1, 11, hw_api)),
    HeapObject<Component>(new ControllerButton(2, 12, hw_api)),
    HeapObject<Component>(new ControllerButton(3, 13, hw_api)),
    HeapObject<Component>(new ControllerButton(4, 14, hw_api)),
    HeapObject<Component>(new ControllerButton(5, 15, hw_api)),
    HeapObject<Component>(new ControllerButton(6, 16, hw_api)),
    HeapObject<Component>(new ControllerButton(7, 17, hw_api)),
    HeapObject<Component>(new ControllerButton(8, 18, hw_api))} {
}


void GameController::begin() {
    Gamepad.begin();
    components.begin();
}

void GameController::loop() {
    components.loop();
}

