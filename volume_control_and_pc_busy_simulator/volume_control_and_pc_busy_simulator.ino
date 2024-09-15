#include "HID-Project.h"
#include "Scheduler.h"
#include "RotaryEncoder.h"
#include "HwApiImpl.h"
#include "DigitalPin.h"

const int DT_PIN = 2;
const int CLK_PIN = 3;
const int SW_PIN = 4;
const int MOUSE_SWITCH_PIN = 5;
const int MOUSE_LED_PIN = 10;
const int KEYBOARD_SWITCH_PIN = 6;
const int KEYBOARD_LED_PIN = 9;

void setup() {
  pinMode(DT_PIN, INPUT_PULLUP);
  pinMode(CLK_PIN, INPUT_PULLUP);
  pinMode(SW_PIN, INPUT_PULLUP);
  pinMode(MOUSE_SWITCH_PIN, INPUT_PULLUP);
  pinMode(MOUSE_LED_PIN, OUTPUT);
  pinMode(KEYBOARD_SWITCH_PIN, INPUT_PULLUP);
  pinMode(KEYBOARD_LED_PIN, OUTPUT);

  Consumer.begin();
  Mouse.begin();
  Serial.begin(9600);
  Serial.println(42);
}

class MouseControl {
public:
  MouseControl(Scheduler& scheduler, HwApi& hw_api) : scheduler{scheduler}, hw_api{hw_api} {
  }

  static void mouseTask(void* self) {
    static_cast<MouseControl*>(self)->move();
  }

  void onSwitch() {
    if (!enabled) {
      task_id = scheduler.addPeriodicTask({mouseTask, this}, 20);
      enabled = true;
      hw_api.digitalWrite(MOUSE_LED_PIN, 1);
      return;
    }

    scheduler.removeTask(task_id);
    hw_api.digitalWrite(MOUSE_LED_PIN, 0);
    enabled = false;
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

private:
  Scheduler& scheduler;
  HwApi& hw_api;
  bool enabled{false};
  SchedulerTaskId task_id{0};
  int moves_made{0};
  int x_increment{3};
  int y_increment{3};
};

class KeyboardControl {
public:
  KeyboardControl(Scheduler& scheduler, HwApi& hw_api) : scheduler{scheduler}, hw_api{hw_api} {
  }

  static void keyboardTask(void* self) {
    static_cast<KeyboardControl*>(self)->press_next_button();
  }

  void onSwitch() {
    if (!enabled) {
      task_id = scheduler.addPeriodicTask({keyboardTask, this}, 300);
      enabled = true;
      next_character = 0;
      hw_api.digitalWrite(KEYBOARD_LED_PIN, 1);
      return;
    }

    scheduler.removeTask(task_id);
    hw_api.digitalWrite(KEYBOARD_LED_PIN, 0);
    enabled = false;
  }

  void press_next_button() {
    static char text[]{"All work and not play makes Jack a dull boy.\n"};
    Keyboard.write(text[next_character]);
    next_character++;
    next_character = next_character % sizeof(text);
  }

private:
  Scheduler& scheduler;
  HwApi& hw_api;
  bool enabled{false};
  SchedulerTaskId task_id{0};
  uint8_t next_character{0};
};

class Controller {
public:
  Controller() {
    encoder.setTurnClockwiseCallback({Controller::onTurnClockwise, nullptr});
    encoder.setTurnCounterClockwiseCallback({Controller::onTurnCounterClockwise, nullptr});
    encoder.setPushButtonCallback({Controller::onPushButton, nullptr});
  }

  static void onTurnClockwise(void*) {
    Consumer.write(MEDIA_VOL_UP);
  }

  static void onTurnCounterClockwise(void*) {
    Consumer.write(MEDIA_VOL_DOWN);
  }

  static void onPushButton(void*) {
    Consumer.write(MEDIA_VOL_MUTE);
  }

  void loop() {
    encoder.readStatus();

    mouse_switch.readPin();
    if (mouse_switch.getPinChange() == PIN_CHANGE::LOW_HIGH) {
      mouse.onSwitch();
    }

    keyboard_switch.readPin();
    if (keyboard_switch.getPinChange() == PIN_CHANGE::LOW_HIGH) {
      keyboard.onSwitch();
    }

    delay(10);
    scheduler.tick(10);
  }

private:
  Scheduler scheduler{};
  HwApiImpl hw_api{};
  MouseControl mouse{scheduler, hw_api};
  KeyboardControl keyboard{scheduler, hw_api};
  RotaryEncoder encoder{DT_PIN, CLK_PIN, SW_PIN, hw_api};
  DigitalPin mouse_switch{MOUSE_SWITCH_PIN, hw_api};
  DigitalPin keyboard_switch{KEYBOARD_SWITCH_PIN, hw_api};
};

Controller controller{};

void loop() {
  controller.loop();
}
