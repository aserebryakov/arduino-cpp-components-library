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
#include <HID-Project.h>
#include "Device.h"
#include "GenericController.h"
#include "HwApi.h"
#include "HeapObject.h"
#include "components/RotaryEncoder.h"

namespace peripherals {

class VolumeControl : public Device {
public:
  VolumeControl(const int dt_pin, const int clk_pin, const int sw_pin, HwApi& hw_api);
  virtual ~VolumeControl() override = default;
  virtual void begin() override;
  virtual void loop() override;

  static void volumeUp(void*);
  static void volumeDown(void*);
  static void mute(void*);

private:
    HwApi& hw_api;
    GenericController<1> control;
};

inline VolumeControl::VolumeControl(const int dt_pin, const int clk_pin, const int sw_pin, HwApi& hw_api) :
  hw_api{hw_api},
  control{
      utility::HeapObject<Component>(new RotaryEncoder{
        {dt_pin, HwApi::PIN_MODE::INPUT_PULLUP_MODE, hw_api},
        {clk_pin, HwApi::PIN_MODE::INPUT_PULLUP_MODE, hw_api},
        {sw_pin, HwApi::PIN_MODE::INPUT_PULLUP_MODE, hw_api},
        {volumeUp, nullptr},
        {volumeDown, nullptr},
        {mute, nullptr}
        })}
{
}

inline void VolumeControl::begin() {
    Consumer.begin();
    control.begin();
}

inline void VolumeControl::loop() {
    control.loop();
}

inline void VolumeControl::volumeUp(void*) {
    Consumer.write(MEDIA_VOL_UP);
    Consumer.write(MEDIA_VOL_UP);
}

inline void VolumeControl::volumeDown(void*) {
    Consumer.write(MEDIA_VOL_DOWN);
    Consumer.write(MEDIA_VOL_DOWN);
}

inline void VolumeControl::mute(void*) {
    Consumer.write(MEDIA_VOL_MUTE);
}

}

#endif //VOLUMECONTROL_H
