
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

#ifndef KEYBOARDCONTROL_H
#define KEYBOARDCONTROL_H

#include "Scheduler.h"
#include <Arduino.h>
#include "HID-Project.h"

namespace peripherals {

class KeyboardLogic {
public:
    KeyboardLogic(Scheduler& scheduler)
      : scheduler{ scheduler } {
    }

    static void keyboardTask(void* self) {
        static_cast<KeyboardLogic*>(self)->press_next_button();
    }

    void begin() {
        Keyboard.begin();
    }

    void start() {
        if (isEnabled()) {
            return;
        }

        task_id = scheduler.addPeriodicTask({ keyboardTask, this }, 300);
        enabled = true;
    }

    void stop() {
        if (!isEnabled()) {
            return;
        }

        scheduler.removeTask(task_id);
        enabled = false;
        next_character = 0;
    }

    void toggle() {
        if (!isEnabled()) {
            start();
        } else {
            stop();
        }
    }

    bool isEnabled() const {
        return enabled;
    }

    void press_next_button() {
        static char text[]{ "All work and no play makes Jack a dull boy.\n" };
        Keyboard.write(text[next_character]);
        next_character++;
        next_character = next_character % sizeof(text);
    }

private:
    Scheduler& scheduler;
    bool enabled{ false };
    SchedulerTaskId task_id{ 0 };
    uint8_t next_character{ 0 };
};

}

#endif //KEYBOARDCONTROL_H
