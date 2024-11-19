#include "HID-Project.h"
#include "RotaryEncoder.h"
#include "DigitalPin.h"
#include "HwApiImpl.h"

#include "GenericController.h"

class TestControl : public Control {
  public:
    TestControl(HwApi& hw_api) : Control{hw_api} {
    }

    virtual void setup() override {}
    virtual void loop() override {}
};


static void pressButton(const int button) {
  Serial.println("Press");
  Serial.println(button);
  Gamepad.press(button);
  Gamepad.write();
  delay(20);
  Gamepad.release(button);
  Gamepad.write();
}

class Button {
  public:
    Button(const int pin, const int button, HwApi& hw_api) : pin{pin, hw_api}, pin_number{pin}, button{button} {}
    
    void setup() {
      pinMode(pin_number, INPUT_PULLUP);
    }

    void read() {
      auto _ = pin.read();
      
      if (pin.getPinChange() != PIN_CHANGE::HIGH_LOW) {
        return;
      }

      pressButton(button);
    }

  private:
    DigitalPin pin;
    int pin_number{0};
    int button{0};
};

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
      rotary3{16, 10, 9, 7, 8, 9, hw_api},
      buttons{
        {0, 10, hw_api},
        {1, 11, hw_api},
        {2, 12, hw_api},
        {3, 13, hw_api},
        {4, 14, hw_api},
        {5, 15, hw_api},
        {6, 16, hw_api},
        {7, 17, hw_api},
        {8, 18, hw_api},
      } {
    }

    void setup() {
      rotary1.setup();
      rotary2.setup();
      rotary3.setup();

      for (auto& button : buttons) {
        button.setup();
      }
    }

    void loop() {
      rotary1.readPins();
      rotary2.readPins();
      rotary3.readPins();

      for (auto& button : buttons) {
        button.read();
      }
    }

  private:
    RotaryEncoderController rotary1;
    RotaryEncoderController rotary2;
    RotaryEncoderController rotary3;
    Button buttons[9];
};

HwApiImpl hw_api{};
Controller controller{hw_api};
GenericController<Control, 1> generic_controller{utility::HeapObject<Control>(new TestControl(hw_api))};


void setup() {
  controller.setup();
  generic_controller.setup();

  Gamepad.begin();
  Serial.begin(9600);
}

void loop() {
  controller.loop();
  generic_controller.loop();
  delay(10);
}