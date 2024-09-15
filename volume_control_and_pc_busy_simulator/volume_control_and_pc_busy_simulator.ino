#include "HID-Project.h"
#include "Scheduler.h"
#include "RotaryEncoder.h"
#include "HwApiImpl.h"
#include "DigitalPin.h"

const int DT_PIN = 2;
const int CLK_PIN = 3;
const int SW_PIN = 4;
const int MOUSE_ON_PIN = 5;

void setup() {
  pinMode(DT_PIN, INPUT_PULLUP);
  pinMode(CLK_PIN, INPUT_PULLUP);
  pinMode(SW_PIN, INPUT_PULLUP);
  pinMode(MOUSE_ON_PIN, INPUT_PULLUP);

  Consumer.begin();
  Mouse.begin();
  Serial.begin(9600);
  Serial.println(42);
}

class MouseControl {
public:
  MouseControl(Scheduler& scheduler) : scheduler{scheduler} {

  }

  static void mouseTask(void* self) {
    static_cast<MouseControl*>(self)->move();
  }

  void onSwitch() {
    if (!enabled) {
      task_id = scheduler.addPeriodicTask({mouseTask, this}, 20);
      enabled = true;
      return;
    }

    scheduler.removeTask(task_id);
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
  bool enabled{false};
  SchedulerTaskId task_id{0};
  int moves_made{0};
  int x_increment{3};
  int y_increment{3};
};

class KeyboardControl {

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

    // Serial.println(hw_api.digitalRead(MOUSE_ON_PIN));
    delay(10);
    scheduler.tick(10);
  }

private:
  Scheduler scheduler{};
  HwApiImpl hw_api{};
  MouseControl mouse{scheduler};
  RotaryEncoder encoder{DT_PIN, CLK_PIN, SW_PIN, hw_api};
  DigitalPin mouse_switch{MOUSE_ON_PIN, hw_api};
};

Controller controller{};

void loop() {
  controller.loop();
}
