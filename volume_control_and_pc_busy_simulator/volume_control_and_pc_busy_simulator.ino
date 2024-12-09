#include "HID-Project.h"
#include "HwApiImpl.h"
#include "GenericController.h"
#include "VolumeControl.h"
#include "Scheduler.h"
#include "MouseControl.h"

using utility::HeapObject;

constexpr int DT_PIN = 7;
constexpr int CLK_PIN = 5;
constexpr int SW_PIN = 2;
constexpr int MOUSE_SWITCH_PIN = 20;
constexpr int MOUSE_LED_PIN = 21;
constexpr int KEYBOARD_SWITCH_PIN = 19;
constexpr int KEYBOARD_LED_PIN = 10;
constexpr int TICK{5};

HwApiImpl hw_api{};

// class KeyboardControl {
// public:
//   KeyboardControl(Scheduler& scheduler, HwApi& hw_api) : scheduler{scheduler}, hw_api{hw_api}, control{
//     HeapObject<Hardware>(new DigitalPin{
//       KEYBOARD_SWITCH_PIN,
//       HwApi::PIN_MODE::INPUT_PULLUP_MODE,
//       {onSwitch, this},
//       {},
//       hw_api
//       })} {
//   }

//   void begin() {
//     Keyboard.begin();
//     hw_api.pinMode(KEYBOARD_LED_PIN, HwApi::PIN_MODE::OUTPUT_MODE);
//     control.begin();
//   }

//   void loop() {
//     control.loop();
//   }

//   static void keyboardTask(void* self) {
//     static_cast<KeyboardControl*>(self)->press_next_button();
//   }

//   static void onSwitch(void* self) {
//     static_cast<KeyboardControl*>(self)->onSwitch();
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
//   GenericController<1> control;
// };

class Controller {
public:
  void begin() {
    volume_control.begin();
    mouse_control.begin();
    // keyboard_control.begin();
  }

  void loop() {
    volume_control.loop();
    mouse_control.loop();
    // keyboard_control.loop();
    scheduler.tick(TICK);
    delay(TICK);
  }

private:
    Scheduler scheduler{};
    peripherals::VolumeControl volume_control{DT_PIN, CLK_PIN, SW_PIN, hw_api};
    peripherals::MouseControl mouse_control{MOUSE_SWITCH_PIN, scheduler, hw_api};
    // KeyboardControl keyboard_control{scheduler, hw_api};
};

Controller controller{};

void setup() {
  controller.begin();
  Serial.begin(9600);
  Serial.println(42);
}

void loop() {
  controller.loop();
}
