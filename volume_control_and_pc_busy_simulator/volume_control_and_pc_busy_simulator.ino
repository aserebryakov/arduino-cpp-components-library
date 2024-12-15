#include "HID-Project.h"
#include "HwApiImpl.h"
#include "VolumeControl.h"
#include "Scheduler.h"
#include "MouseControl.h"
#include "KeyboardControl.h"

constexpr int DT_PIN = 7;
constexpr int CLK_PIN = 5;
constexpr int SW_PIN = 2;
constexpr int MOUSE_SWITCH_PIN = 20;
constexpr int MOUSE_LED_PIN = 21;
constexpr int KEYBOARD_SWITCH_PIN = 19;
constexpr int KEYBOARD_LED_PIN = 10;
constexpr int TICK{ 5 };

HwApiImpl hw_api{};

class MouseControl : public Device {
public:
  MouseControl(const int switch_pin, const int led_pin, Scheduler& scheduler, HwApi& hw_api) :
      jiggler{scheduler},
      button{
              {switch_pin, true},
              hw_api,
              {onSwitch, this},
              {}
      },
    led{led_pin, hw_api} {
  }

  virtual ~MouseControl() override = default;

  void begin() {
    button.begin();
  }

  void loop() {
    button.loop();
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
  peripherals::MouseJigglerLogic jiggler;
  Button button;
  DigitalLed led;
};

class KeyboardControl : public Device {
public:
  KeyboardControl(const int switch_pin, const int led_pin, Scheduler& scheduler, HwApi& hw_api)
    : keyboard_logic{ scheduler },
      button{
        { switch_pin, true },
        hw_api,
        { onSwitch, this },
        {}
      },
      led{ led_pin, hw_api } {
  }

  void begin() {
    button.begin();
    led.begin();
  }

  void loop() {
    button.loop();
  }

  static void onSwitch(void* self) {
    auto& this_{ *(static_cast<KeyboardControl*>(self)) };
    this_.keyboard_logic.toggle();

    if (this_.keyboard_logic.isEnabled()) {
      this_.led.turnOn();
    } else {
      this_.led.turnOff();
    }
  }

private:
  peripherals::KeyboardLogic keyboard_logic;
  Button button;
  DigitalLed led;
};

class Controller {
public:
  void begin() {
    volume_control.begin();
    mouse_control.begin();
    keyboard_control.begin();
  }

  void loop() {
    volume_control.loop();
    mouse_control.loop();
    keyboard_control.loop();
    scheduler.tick(TICK);
    delay(TICK);
  }

private:
  Scheduler scheduler{};
  peripherals::VolumeControl volume_control{ DT_PIN, CLK_PIN, SW_PIN, hw_api };
  MouseControl mouse_control{ MOUSE_SWITCH_PIN, MOUSE_LED_PIN, scheduler, hw_api };
  KeyboardControl keyboard_control{ KEYBOARD_SWITCH_PIN, KEYBOARD_LED_PIN, scheduler, hw_api };
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
