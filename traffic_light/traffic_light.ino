/*
  Fade

  This example shows how to fade an LED on pin 9 using the analogWrite()
  function.

  The analogWrite() function uses PWM, so if you want to change the pin you're
  using, be sure to use another PWM capable pin. On most Arduino, the PWM pins
  are identified with a "~" sign,                              ~3, ~5, ~6, ~9, ~10 and ~11.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Fade
*/

const int RED_LED = 9;
const int YELLOW_LED = 10;
const int GREEN_LED = 11;
int TIME = 1000;
const int DELAY_PIN = A0;

const int BRIGHTNESS = 64;  // how bright the LED is

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  // pinMode(DELAY_PIN, OUTPUT);
  Serial.begin(9600);
}

void reset() {
  TIME = analogRead(DELAY_PIN) * 3;
  Serial.println(TIME);
  analogWrite(RED_LED, 0);
  analogWrite(YELLOW_LED, 0);
  analogWrite(GREEN_LED, 0);
}

void red() {
  reset();
  analogWrite(RED_LED, BRIGHTNESS);
  delay(TIME);
}

void red_yellow() {
  reset();
  analogWrite(RED_LED, BRIGHTNESS);
  analogWrite(YELLOW_LED, BRIGHTNESS);
  delay(TIME);
}

void green() {
  reset();
  analogWrite(GREEN_LED, BRIGHTNESS / 4);
  delay(TIME);
}

void green_blinking() {
  for (int i = 0; i < 4; i++) {
    reset();
    delay(TIME / 4);
    analogWrite(GREEN_LED, BRIGHTNESS / 4);
    delay(TIME / 4);
  }
}

void yellow() {
  reset();
  analogWrite(YELLOW_LED, BRIGHTNESS);
  delay(TIME);
}

// the loop routine runs over and over again forever:`
void loop() {
  red();
  red_yellow();
  green();
  green_blinking();
  yellow();
}
