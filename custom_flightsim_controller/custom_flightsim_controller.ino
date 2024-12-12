#include "HwApiImpl.h"
#include "HID-Project.h"
#include "GameController.h"

HwApiImpl hw_api{};
GameController game_controller{hw_api};

void setup() {
  Serial.begin(9600);
  game_controller.begin();
}

void loop() {
  game_controller.loop();
  delay(5);
}