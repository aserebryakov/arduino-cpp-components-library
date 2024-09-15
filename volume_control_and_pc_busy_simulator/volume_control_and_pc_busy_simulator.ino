#include "HID-Project.h"
#include "Scheduler.h"
#include "RotaryEncoder.h"
#include "RotaryEncoderPin.h"
#include "HwApiImpl.h"

const int DT_PIN = 2;
const int CLK_PIN = 3;
const int SW_PIN = 4;

void setup() {
  pinMode(DT_PIN, INPUT_PULLUP);
  pinMode(CLK_PIN, INPUT_PULLUP);
  pinMode(SW_PIN, INPUT_PULLUP);

  Consumer.begin();
  Serial.begin(9600);
  Serial.println(42);
}

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
  }

private:
  HwApiImpl hw_api{};
  RotaryEncoderPin dt{DT_PIN, hw_api};
  RotaryEncoderPin clk{CLK_PIN, hw_api};
  RotaryEncoderPin sw{SW_PIN, hw_api};
  RotaryEncoder encoder{dt, clk, sw};
};

Controller controller{};

void loop() {
  controller.loop();
  delay(10);
}
