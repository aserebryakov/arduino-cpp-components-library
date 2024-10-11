#include "HID-Project.h"
#include "RotaryEncoder.h"
#include "HwApiImpl.h"

class RotaryEncoderController {
  public:
    RotaryEncoderController(const int dt_pin,
                            const int clk_pin,
                            const int sw_pin,
                            const int turn_clockwise_button,
                            const int turn_counterclockwise_button,
                            const int switch_button,
                            HwApi& hw_api) :
                              encoder{dt_pin, clk_pin, sw_pin, hw_api},
                              dt_pin{dt_pin},
                              clk_pin{clk_pin},
                              sw_pin{sw_pin},
                              turn_clockwise_button{turn_clockwise_button},
                              turn_counterclockwise_button{turn_counterclockwise_button},
                              switch_button{switch_button} {
        encoder.setPushButtonCallback({onPushButtonCallback, this});
        encoder.setTurnClockwiseCallback({onTurnClockwiseCallback, this});
        encoder.setTurnCounterClockwiseCallback({onTurnCounterclockwiseCallback, this});
    }

    void setup() {
      pinMode(dt_pin, INPUT);
      pinMode(clk_pin, INPUT);
      pinMode(sw_pin, INPUT);
    }

    void readPins() {
      encoder.readPins();
    }

  private:
    static void onTurnClockwiseCallback(void* self) {
      static_cast<RotaryEncoderController*>(self)->onTurnClockwise();
    }

    static void pressButton(const int button) {
      Serial.println(button);
      Gamepad.press(button);
      Gamepad.write();
      Gamepad.release(button);
      Gamepad.write();
    }

    void onTurnClockwise() {
      Serial.println("Clockwise");
      pressButton(turn_clockwise_button);
    }

    static void onTurnCounterclockwiseCallback(void* self) {
      static_cast<RotaryEncoderController*>(self)->onTurnCounterclockwise();
    }

    void onTurnCounterclockwise() {
      Serial.println("Counterclockwise");
      pressButton(turn_counterclockwise_button);
    }

    static void onPushButtonCallback(void* self) {
      static_cast<RotaryEncoderController*>(self)->onPushButton();
    }

    void onPushButton() {
      Serial.println("Push");
      pressButton(switch_button);
    }

    RotaryEncoder encoder;
    int dt_pin{};
    int clk_pin{};
    int sw_pin{};
    int turn_clockwise_button{};
    int turn_counterclockwise_button{};
    int switch_button{};
};

class Controller {
  public:
    Controller(HwApi& hw_api) :
      rotary1{21, 20, 19, 1, 2, 3, hw_api},
      rotary2{18, 15, 14, 4, 5, 6, hw_api},
      rotary3{16, 10, 9, 7, 8, 9, hw_api} {
    }

    void setup() {
      rotary1.setup();
      rotary2.setup();
      rotary3.setup();
    }

    void loop() {
      rotary1.readPins();
      rotary2.readPins();
      rotary3.readPins();
    }

  private:
    RotaryEncoderController rotary1;
    RotaryEncoderController rotary2;
    RotaryEncoderController rotary3;
};

HwApiImpl hw_api{};
Controller controller{hw_api};

void setup() {
  controller.setup();

  Gamepad.begin();
  Serial.begin(9600);
}

void loop() {
  controller.loop();
  delay(10);
}