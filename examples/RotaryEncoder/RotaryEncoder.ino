#include <Arduino.h>
#include <CppComponentsLibrary.h>

HwApiImpl hw_api{};

constexpr int DT_PIN{3};
constexpr int SW_PIN{4};
constexpr int CLK_PIN{2};

class RotaryEncoderLogic : public Device {
public:
  RotaryEncoderLogic() : encoder{
    {DT_PIN, true},
    {CLK_PIN, true},
    {SW_PIN, true},
    hw_api,
    {onTurnClockwise, this},
    {onTurnCounterClockwise, this},
    {onTurnPushButton, this}
    }
  {
  }

  virtual ~RotaryEncoderLogic() = default;

  virtual void begin() override {
    encoder.begin();
  }

  virtual void loop() override {
    encoder.loop();
  }

  static void onTurnClockwise(void* self) {
    auto& logic{*static_cast<RotaryEncoderLogic*>(self)};
    logic.counter++;
    Serial.print("Turn clockwise : ");
    Serial.println(logic.counter);
  }

  static void onTurnCounterClockwise(void* self) {
    auto& logic{*static_cast<RotaryEncoderLogic*>(self)};
    logic.counter--;
    Serial.print("Turn counter clockwise : ");
    Serial.println(logic.counter);
  }

  static void onTurnPushButton(void* self) {
    auto& logic{*static_cast<RotaryEncoderLogic*>(self)};
    logic.counter = 0;
    Serial.print("Push button : ");
    Serial.println(logic.counter);
  }

private:
  RotaryEncoder encoder;
  int counter{0};
};

RotaryEncoderLogic logic{};

void setup() {
  Serial.begin(57600);
  logic.begin();
}

void loop() {
  logic.loop();
  delay(5);
}
