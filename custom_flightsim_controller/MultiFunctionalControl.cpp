
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

#include "MultiFunctionalControl.h"

MultiFunctionalControl::MultiFunctionalControl(Scheduler& scheduler, HwApi& hw_api) :
  volume_control{21, 20, 19, hw_api},
  mouse_jiggler{1, scheduler, hw_api},
  keyboard_emulator{3, scheduler, hw_api} {
}

void MultiFunctionalControl::begin() {
  mouse_jiggler.begin();
  keyboard_emulator.begin();
  volume_control.begin();
}

void MultiFunctionalControl::loop() {
  mouse_jiggler.loop();
  keyboard_emulator.loop();
  volume_control.loop();
}