
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
#ifndef MOUSECONTROL_H
#define MOUSECONTROL_H

#include <Arduino.h>
#include <HID-Project.h>
#include "HwApi.h"
#include "Scheduler.h"
#include "HwApi.h"
#include "Device.h"
#include "ComponentsComposition.h"
#include "HeapObject.h"
#include "Button.h"
#include "DigitalLed.h"


namespace peripherals {

class MouseJigglerLogic {
public:
    MouseJigglerLogic(Scheduler& scheduler) : scheduler{scheduler} {
    }

    static void mouseTask(void* self) {
        static_cast<MouseJigglerLogic*>(self)->move();
    }

    void begin() {
        Mouse.begin();
    }

    void move() {
        Mouse.move(x_increment, y_increment);
        moves_made++;
        if (moves_made % 60 == 0) {
            x_increment = -x_increment;
            y_increment = -y_increment;
            Mouse.click();
        }
    }

    void toggle() {
        if (!enabled) {
            task_id = scheduler.addPeriodicTask({mouseTask, this}, 20);
            enabled = true;
            return;
        }

        scheduler.removeTask(task_id);
        enabled = false;
    }

    bool isEnabled() const {
      return enabled;
    }

private:
    Scheduler& scheduler;
    bool enabled{false};
    SchedulerTaskId task_id{0};
    int moves_made{0};
    int x_increment{3};
    int y_increment{3};
};

class MouseControl : public Device {
public:
    MouseControl(const int switch_pin, const int led_pin, Scheduler& scheduler, HwApi& hw_api) : jiggler{scheduler}, hw_api{hw_api}, control{
        utility::HeapObject<Component>(new Button{
          {switch_pin, true},
          hw_api,
          {onSwitch, this},
          {},
          })},
  		led{led_pin, hw_api} {
    }

    virtual ~MouseControl() override = default;

    void begin() {
        control.begin();
    }

    void loop() {
        control.loop();
    }

    static void onSwitch(void* self) {
        auto& this_ = *(static_cast<MouseControl*>(self));
        this_.jiggler.toggle();

        if (this_.jiggler.isEnabled()) {
          this_.led.turnOn();
        } else {
          this_.led.turnOff();
        }
    }

private:
    MouseJigglerLogic jiggler;
    HwApi& hw_api;
    ComponentsComposition<1> control;
    DigitalLed led;
};

}

#endif //MOUSECONTROL_H