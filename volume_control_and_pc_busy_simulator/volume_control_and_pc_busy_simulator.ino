#include "HID-Project.h"

const int OUT_A = 2;
const int OUT_B = 3;
const int SWITCH = 4;

enum class PIN_CHANGE {
  LOW_HIGH,
  HIGH_LOW,
  NO_CHANGE
};


class RotaryPin {
public:
  RotaryPin(const int pin_number) : pin_number{pin_number} {}; 

  PIN_CHANGE read_changed() {
    const bool current{digitalRead(pin_number) == LOW};
    Serial.println(current);

    if (current == state) {
      return PIN_CHANGE::NO_CHANGE;
    }

    state = current;
    return state ? PIN_CHANGE::LOW_HIGH : PIN_CHANGE::HIGH_LOW;
  }

  bool get_state() const {
    return state;
  }

private:
  int pin_number;
  bool state{false};
};

void setup() {
  pinMode(OUT_A, INPUT_PULLUP);
  pinMode(OUT_B, INPUT_PULLUP);
  pinMode(SWITCH, INPUT_PULLUP);

  Consumer.begin();
  Serial.begin(9600);
  Serial.println(42);
}

RotaryPin A{OUT_A};
RotaryPin B{OUT_B};
RotaryPin Switch{SWITCH};

void loop() {                                    
  const auto a_direction{A.read_changed()};

  if (a_direction == PIN_CHANGE::LOW_HIGH) {
    B.read_changed();
    if (B.get_state()) {
      Consumer.write(MEDIA_VOL_UP);
    } else {
      Consumer.write(MEDIA_VOL_DOWN);
    }
  }

  delay(10);
}
