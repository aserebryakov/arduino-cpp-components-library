#include <Arduino.h>
#include "HwApiImpl.h"
#include "HID-Project.h"
#include "GameController.h"
#include "VolumeControl.h"

HwApiImpl hw_api{};
GameController game_controller{hw_api};
utility::HeapObject<Device> device{nullptr};

constexpr int CONFIGURATION_PIN{7};

void setup() {
  Serial.begin(9600);
  hw_api.pinMode(CONFIGURATION_PIN, HwApi::PIN_MODE::INPUT_PULLUP_MODE);

  if (hw_api.digitalRead(CONFIGURATION_PIN) == HwApi::DIGITAL_PIN_LEVEL::LEVEL_HIGH) {
    Serial.println("Game Controller Selected");
    device = utility::HeapObject<Device>(new GameController(hw_api));
  } else {
    device = utility::HeapObject<Device>(new peripherals::VolumeControl(21, 20, 19, hw_api));
  }

  device->begin();
}

void loop() {
  device->loop();
  delay(5);
}