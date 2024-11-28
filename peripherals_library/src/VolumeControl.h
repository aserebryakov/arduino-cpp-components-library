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
#ifndef VOLUMECONTROL_H
#define VOLUMECONTROL_H

#include <Arduino.h>
#include "DeviceApi.h"
#include "GenericController.h"
#include "HwApi.h"
#include <HID-Project.h>
//#if !defined(USBCON)
//#error HID Project can only be used with an USB MCU.
//#endif

namespace peripherals {

class VolumeControl : public DeviceApi {
public:
  VolumeControl(const int dt_pin, const int clk_pin, const int sw_pin, HwApi& hw_api);
  virtual ~VolumeControl() = default;
  virtual void setup() override;
  virtual void loop() override;

  static void volumeUp(void*);
  static void volumeDown(void*);
  static void mute(void*);

private:
    HwApi& hw_api;
    GenericController<1> control;
};

}

#endif //VOLUMECONTROL_H
