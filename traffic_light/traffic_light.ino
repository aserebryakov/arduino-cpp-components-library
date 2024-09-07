/**
 * Simple traffic light control.
 * Board: atmega328p
 */
const int RED_LED{9};
const int YELLOW_LED{10};
const int GREEN_LED{11};
const int DELAY_PIN{A0};
const int BRIGHTNESS{64};  // how bright the LED is

const int BUTTON_PIN{4};

int TIME{1000};

class TrafficLightColorSetter {
  public:
    static void green();
    static void yellow();
    static void red();
    static void red_yellow();
    static void off();
};

using TrafficLightColorSet = void (*)();

void TrafficLightColorSetter::off() {
  analogWrite(RED_LED, 0);
  analogWrite(YELLOW_LED, 0);
  analogWrite(GREEN_LED, 0);
}

void TrafficLightColorSetter::red() {
  off();
  analogWrite(RED_LED, BRIGHTNESS);
}

void TrafficLightColorSetter::red_yellow() {
  off();
  analogWrite(RED_LED, BRIGHTNESS);
  analogWrite(YELLOW_LED, BRIGHTNESS);
}

void TrafficLightColorSetter::green() {
  off();
  analogWrite(GREEN_LED, BRIGHTNESS / 4);
}

void TrafficLightColorSetter::yellow() {
  off();
  analogWrite(YELLOW_LED, BRIGHTNESS);
}

class TrafficLightControl {
  public:
    void loop_callback();

  private:
    int32_t read_multiplier() const;
    bool button_pressed() const;
    void change_state();

    static constexpr int GREEN{8};
    static constexpr int GREEN_BLINKING_ON{1};
    static constexpr int GREEN_BLINKING_OFF{1};
    static constexpr int YELLOW{3};
    static constexpr int RED{11};
    static constexpr int RED_YELLOW{1};

    static int durations[];
    static TrafficLightColorSet states_handlers[];

    int current_msecs{0};
    size_t current_state{0};
};

int TrafficLightControl::durations[] = {
  GREEN,
  GREEN_BLINKING_OFF,
  GREEN_BLINKING_ON,
  GREEN_BLINKING_OFF,
  GREEN_BLINKING_ON,
  GREEN_BLINKING_OFF,
  GREEN_BLINKING_ON,
  YELLOW,
  RED,
  RED_YELLOW
  };

TrafficLightColorSet TrafficLightControl::states_handlers[] = {
  TrafficLightColorSetter::green,
  TrafficLightColorSetter::off,
  TrafficLightColorSetter::green,
  TrafficLightColorSetter::off,
  TrafficLightColorSetter::green,
  TrafficLightColorSetter::off,
  TrafficLightColorSetter::green,
  TrafficLightColorSetter::yellow,
  TrafficLightColorSetter::red,
  TrafficLightColorSetter::red_yellow
  };

void TrafficLightControl::change_state() {
  // Serial.println(current_state);

  current_state = current_state + 1;

  if (current_state >= sizeof(durations)/sizeof(int)) {
    // Serial.println("Reseting state");
    current_state = 0;
  }

  // Serial.print("Current state: ");
  // Serial.println(current_state);
  (*states_handlers[current_state])();
}

void TrafficLightControl::loop_callback() {
  constexpr int INTERVAL{100};
  current_msecs += INTERVAL;

  if (current_msecs > durations[current_state] * read_multiplier()) {
    change_state();
    current_msecs = 0;
  }

  if (button_pressed() && current_state == 0) {
    change_state();
    current_msecs = 0;
  }

  delay(INTERVAL);
}

int32_t TrafficLightControl::read_multiplier() const {
  const int32_t pin_value{analogRead(DELAY_PIN)};
  // Serial.println(pin_value);
  const int32_t multiplier{(pin_value * 2000) / 1024 + 200};
  // Serial.println(multiplier);
  return multiplier;
}

bool TrafficLightControl::button_pressed() const {
  return digitalRead(BUTTON_PIN) == 0;
}

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);

  TrafficLightColorSetter::green(); // Just to setup initial state
  Serial.println(42); // If you see this in the log more than once - code just crashed =)
}

TrafficLightControl control{};

void loop() {
  control.loop_callback();
}
