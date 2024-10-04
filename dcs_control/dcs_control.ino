#include "HID-Project.h"
#include "RotaryEncoder.h"
#include "HwApiImpl.h"

const int pinLed = LED_BUILTIN;
const int pinButton = 2;
constexpr int DT_PIN{ 4 };
constexpr int CLK_PIN{ 5 };
constexpr int SW_PIN{ 3 };

HwApiImpl hw_api{};
RotaryEncoder encoder{ DT_PIN, CLK_PIN, SW_PIN, hw_api };


void onTurnRight(void*) {
  Gamepad.press(1);
  Gamepad.write();
  Gamepad.releaseAll();
  Gamepad.write();

  Serial.println("Right");
  Serial.println(digitalRead(SW_PIN));
  Serial.println(digitalRead(DT_PIN));
  Serial.println(digitalRead(CLK_PIN));
}

void onTurnLeft(void*) {
  Gamepad.press(2);
  Gamepad.write();
  Gamepad.releaseAll();
  Gamepad.write();


  Serial.println("Left");
  Serial.println(digitalRead(SW_PIN));
  Serial.println(digitalRead(DT_PIN));
  Serial.println(digitalRead(CLK_PIN));
}

void onClick(void*) {
  Gamepad.press(3);
  Gamepad.write();
  Gamepad.releaseAll();
  Gamepad.write();


  Serial.println("Click");
  Serial.println(digitalRead(SW_PIN));
  Serial.println(digitalRead(DT_PIN));
  Serial.println(digitalRead(CLK_PIN));
}

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);
  pinMode(DT_PIN, INPUT);
  pinMode(CLK_PIN, INPUT);
  pinMode(SW_PIN, INPUT);

  //   pinMode(DT_PIN, INPUT_PULLUP);
  // pinMode(CLK_PIN, INPUT_PULLUP);
  // pinMode(SW_PIN, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  Gamepad.begin();
  Serial.begin(9600);

  encoder.setPushButtonCallback({ onClick, nullptr });
  encoder.setTurnClockwiseCallback({ onTurnRight, nullptr });
  encoder.setTurnCounterClockwiseCallback({ onTurnLeft, nullptr });
}

void loop() {
  encoder.readRotation();
  encoder.readStatus();

  // Serial.println(digitalRead(SW_PIN));
  // Serial.println(digitalRead(DT_PIN));
  // Serial.println(digitalRead(CLK_PIN));
  // Serial.println(digitalRead(pinButton));


  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // Press button 1-32
    static uint8_t count = 0;
    count++;
    if (count == 33) {
      Gamepad.releaseAll();
      count = 0;
    } else
      Gamepad.press(count);

    // Move x/y Axis to a new position (16bit)
    Gamepad.xAxis(random(0xFFFF));
    Gamepad.yAxis(random(0xFFFF));

    // Go through all dPad positions
    // values: 0-8 (0==centered)
    static uint8_t dpad1 = GAMEPAD_DPAD_CENTERED;
    Gamepad.dPad1(dpad1++);
    if (dpad1 > GAMEPAD_DPAD_UP_LEFT)
      dpad1 = GAMEPAD_DPAD_CENTERED;

    static int8_t dpad2 = GAMEPAD_DPAD_CENTERED;
    Gamepad.dPad2(dpad2--);
    if (dpad2 < GAMEPAD_DPAD_CENTERED)
      dpad2 = GAMEPAD_DPAD_UP_LEFT;

    // Functions above only set the values.
    // This writes the report to the host.
    Gamepad.write();

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }

  delay(10);
}