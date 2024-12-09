
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
#include "GenericController.h"
#include "HeapObject.h"
#include "Button.h"


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
//            hw_api.digitalWrite(MOUSE_LED_PIN, 1);
            return;
        }

        scheduler.removeTask(task_id);
//        hw_api.digitalWrite(MOUSE_LED_PIN, 0);
        enabled = false;
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
    MouseControl(const int switch_pin, Scheduler& scheduler, HwApi& hw_api) : jiggler{scheduler}, hw_api{hw_api}, control{
        utility::HeapObject<Component>(new Button{
          {switch_pin, true},
          hw_api,
          {onSwitch, this},
          {},
          })} {
    }

    virtual ~MouseControl() override = default;

    void begin() {
//        hw_api.pinMode(MOUSE_LED_PIN, HwApi::PIN_MODE::OUTPUT_MODE);
        control.begin();
    }

    void loop() {
        control.loop();
    }

    static void onSwitch(void* self) {
        static_cast<MouseControl*>(self)->jiggler.toggle();
    }

private:
    MouseJigglerLogic jiggler;
    HwApi& hw_api;
    GenericController<1> control;
};

}

#endif //MOUSECONTROL_H
