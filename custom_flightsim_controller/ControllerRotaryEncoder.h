
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

#ifndef CONTROLLERROTARYENCODER_H
#define CONTROLLERROTARYENCODER_H

#include "RotaryEncoder.h"
#include "Component.h"
#include <Arduino.h>
#include "HID-Project.h"
#include "PressButton.h"


class ControllerRotaryEncoder : public Component {
public:
  ControllerRotaryEncoder(const int dt_pin,
                          const int clk_pin,
                          const int sw_pin,
                          const int turn_clockwise_button,
                          const int turn_counterclockwise_button,
                          const int switch_button,
                          HwApi& hw_api)
    : encoder{ { dt_pin, false },
               { clk_pin, false },
               { sw_pin, false },
               hw_api,
               { onTurnClockwiseCallback, this },
               { onTurnCounterclockwiseCallback, this },
               { onPushButtonCallback, this } },
      turn_clockwise_button{ turn_clockwise_button },
      turn_counterclockwise_button{ turn_counterclockwise_button },
      switch_button{ switch_button } {}

  virtual void
  begin() override {
    encoder.begin();
  }

  virtual void
  loop() override {
    encoder.loop();
  }

private:
  static void onTurnClockwiseCallback(void* self) {
    static_cast<ControllerRotaryEncoder*>(self)->onTurnClockwise();
  }

  void onTurnClockwise() {
    Serial.println("Clockwise");
    pressButton(turn_clockwise_button);
  }

  static void onTurnCounterclockwiseCallback(void* self) {
    static_cast<ControllerRotaryEncoder*>(self)->onTurnCounterclockwise();
  }

  void onTurnCounterclockwise() {
    Serial.println("Counterclockwise");
    pressButton(turn_counterclockwise_button);
  }

  static void onPushButtonCallback(void* self) {
    static_cast<ControllerRotaryEncoder*>(self)->onPushButton();
  }

  void onPushButton() {
    Serial.println("Push");
    pressButton(switch_button);
  }

  RotaryEncoder encoder;
  int turn_clockwise_button{};
  int turn_counterclockwise_button{};
  int switch_button{};
};


#endif  //CONTROLLERROTARYENCODER_H
