#include "HID-Project.h"
#include "Scheduler.h"
#include "RotaryEncoder.h"
#include "HwApiImpl.h"
#include "DigitalPin.h"
#include "GenericController.h"

using utility::HeapObject;

const int DT_PIN = 7;
const int CLK_PIN = 5;
const int SW_PIN = 2;
const int MOUSE_SWITCH_PIN = 20;
const int MOUSE_LED_PIN = 21;
const int KEYBOARD_SWITCH_PIN = 19;
const int KEYBOARD_LED_PIN = 10;
constexpr int TICK{5};

HwApiImpl hw_api{};

class VolumeControl {
public:
  void setup() {
    Consumer.begin();
  }

  void loop() {
  }

  static void volumeUp(void*) {
    Consumer.write(MEDIA_VOL_UP);
    Consumer.write(MEDIA_VOL_UP);
  }

  static void volumeDown(void*) {
    Consumer.write(MEDIA_VOL_DOWN);
    Consumer.write(MEDIA_VOL_DOWN);
  }

  static void mute(void*) {
    Consumer.write(MEDIA_VOL_MUTE);
  }
};


class MouseControl {
public:
  MouseControl(Scheduler& scheduler, HwApi& hw_api) : scheduler{scheduler}, hw_api{hw_api} {
  }

  void setup() {
    hw_api.pinMode(MOUSE_LED_PIN, HwApi::PIN_MODE::OUTPUT_MODE);
    Mouse.begin();
  }

  static void mouseTask(void* self) {
    static_cast<MouseControl*>(self)->move();
  }

  static void onSwitch(void* self) {
    static_cast<MouseControl*>(self)->onSwitch();
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

class Controller {
public:
  void setup() {
    control.setup();
    volume_control.setup();
    mouse_control.setup();
  }

  void loop() {
    control.loop();
    volume_control.loop();
    scheduler.tick(TICK);
    delay(TICK);
  }

private:
    Scheduler scheduler{};
    VolumeControl volume_control{};
    MouseControl mouse_control{scheduler, hw_api};

    GenericController<Control, 2> control{
      HeapObject<Control>(new RotaryEncoder{
        {DT_PIN, HwApi::PIN_MODE::INPUT_PULLUP_MODE, hw_api},
        {CLK_PIN, HwApi::PIN_MODE::INPUT_PULLUP_MODE, hw_api},
        {SW_PIN, HwApi::PIN_MODE::INPUT_PULLUP_MODE, hw_api},
        {VolumeControl::volumeUp, nullptr},
        {VolumeControl::volumeDown, nullptr},
        {VolumeControl::mute, nullptr}
        }),
      HeapObject<Control>(new DigitalPin{
        MOUSE_SWITCH_PIN,
        HwApi::PIN_MODE::INPUT_PULLUP_MODE,
        {MouseControl::onSwitch, &mouse_control},
        {},
        hw_api
        })};
};

Controller controller{};

void setup() {
  // pinMode(KEYBOARD_SWITCH_PIN, INPUT_PULLUP);
  // pinMode(KEYBOARD_LED_PIN, OUTPUT);

  controller.setup();
  Serial.begin(9600);
  Serial.println(42);
}

void loop() {
  controller.loop();
}


// class KeyboardControl {
// public:
//   KeyboardControl(Scheduler& scheduler, HwApi& hw_api) : scheduler{scheduler}, hw_api{hw_api} {
//   }

//   static void keyboardTask(void* self) {
//     static_cast<KeyboardControl*>(self)->press_next_button();
//   }

//   void onSwitch() {
//     if (!enabled) {
//       task_id = scheduler.addPeriodicTask({keyboardTask, this}, 200);
//       enabled = true;
//       next_character = 0;
//       hw_api.digitalWrite(KEYBOARD_LED_PIN, 1);
//       return;
//     }

//     scheduler.removeTask(task_id);
//     hw_api.digitalWrite(KEYBOARD_LED_PIN, 0);
//     enabled = false;
//   }

//   void press_next_button() {
//     static char text[]{"All work and no play makes Jack a dull boy.\n"};
//     Keyboard.write(text[next_character]);
//     next_character++;
//     next_character = next_character % sizeof(text);
//   }

// private:
//   Scheduler& scheduler;
//   HwApi& hw_api;
//   bool enabled{false};
//   SchedulerTaskId task_id{0};
//   uint8_t next_character{0};
// };

// class Controller {
// public:
//   Controller() {
//     encoder.setTurnClockwiseCallback({Controller::onTurnClockwise, nullptr});
//     encoder.setTurnCounterClockwiseCallback({Controller::onTurnCounterClockwise, nullptr});
//     encoder.setPushButtonCallback({Controller::onPushButton, nullptr});
//   }

//   static void onTurnClockwise(void*) {
//     Consumer.write(MEDIA_VOL_UP);
//     Consumer.write(MEDIA_VOL_UP);
//   }

//   static void onTurnCounterClockwise(void*) {
//     Consumer.write(MEDIA_VOL_DOWN);
//     Consumer.write(MEDIA_VOL_DOWN);
//   }

//   static void onPushButton(void*) {
//     Consumer.write(MEDIA_VOL_MUTE);
//   }

//   void loop() {
//     encoder.readPins();

//     mouse_switch.read();
//     if (mouse_switch.getPinChange() == PIN_CHANGE::LOW_HIGH) {
//       mouse.onSwitch();
//     }

//     keyboard_switch.read();
//     if (keyboard_switch.getPinChange() == PIN_CHANGE::LOW_HIGH) {
//       keyboard.onSwitch();
//     }

//     delay(10);
//     scheduler.tick(10);
//   }

// private:
//   Scheduler scheduler{};
//   HwApiImpl hw_api{};
//   MouseControl mouse{scheduler, hw_api};
//   KeyboardControl keyboard{scheduler, hw_api};
//   RotaryEncoder encoder{DT_PIN, CLK_PIN, SW_PIN, hw_api};
//   DigitalPin mouse_switch{MOUSE_SWITCH_PIN, hw_api};
//   DigitalPin keyboard_switch{KEYBOARD_SWITCH_PIN, hw_api};
// };

// Controller controller{};

