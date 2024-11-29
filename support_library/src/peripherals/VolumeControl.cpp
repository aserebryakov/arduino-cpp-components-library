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

//#define USBCON // The actual check is propagated to header.
#include "VolumeControl.h"
#include "HeapObject.h"
#include "RotaryEncoder.h"
#include "HID-Project.h"

namespace peripherals {

VolumeControl::VolumeControl(const int dt_pin, const int clk_pin, const int sw_pin, HwApi& hw_api) :
  hw_api{hw_api},
  control{
      utility::HeapObject<Hardware>(new RotaryEncoder{
        {dt_pin, HwApi::PIN_MODE::INPUT_PULLUP_MODE, hw_api},
        {clk_pin, HwApi::PIN_MODE::INPUT_PULLUP_MODE, hw_api},
        {sw_pin, HwApi::PIN_MODE::INPUT_PULLUP_MODE, hw_api},
        {volumeUp, nullptr},
        {volumeDown, nullptr},
        {mute, nullptr}
        })}
{
}

void VolumeControl::setup() {
  Consumer.begin();
  control.setup();
}

void VolumeControl::loop() {
  control.loop();
}

void VolumeControl::volumeUp(void*) {
  Consumer.write(MEDIA_VOL_UP);
  Consumer.write(MEDIA_VOL_UP);
}

void VolumeControl::volumeDown(void*) {
  Consumer.write(MEDIA_VOL_DOWN);
  Consumer.write(MEDIA_VOL_DOWN);
}

void VolumeControl::mute(void*) {
  Consumer.write(MEDIA_VOL_MUTE);
}

}