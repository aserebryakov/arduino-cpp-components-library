// MIT License
//
// Copyright (c) 2025 Alexander Serebryakov
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// This example demonstrates how to work with RotaryEncoder object.
//
// Hardware:
// - Arduino
// - KY-40 rotary encoder
//
// Setup:
// - DT pin is connected to D3
// - SW pin is connected to D4
// - CLK pin is connected to D2

#include <Arduino.h>
#include <CppComponentsLibrary.h>

// Instantiate a hardware api object.
HwApiImpl hw_api{};

constexpr int DT_PIN{3};
constexpr int SW_PIN{4};
constexpr int CLK_PIN{2};

// Class is used to implement callbacks and store the internal state.
//
// Inheritance from Device class isn't necessary, but it provides default functions
// to be implemented to have a consistent API
class RotaryEncoderLogic : public Device {
public:
  RotaryEncoderLogic() : encoder{
    {DT_PIN, true}, // Setting DT pin to PULL_UP mode
    {CLK_PIN, true}, // Setting CLK pin to PULL_UP mode
    {SW_PIN, true}, // Setting SW pin to PULL_UP mode
    hw_api, // Providing to encoder instance of HwApi to be used to control pins
    {onTurnClockwise, this}, // Connecting clockwise turn event to callback function and this object
    {onTurnCounterClockwise, this}, // Connecting counter clockwise turn event to callback function and this object 
    {onTurnPushButton, this} // Connecting button push event to callback function and this object
    }
  {
  }

  virtual ~RotaryEncoderLogic() = default;

  // Function to be called from setup() 
  virtual void begin() override {
    encoder.begin(); // Initializes pins
  }

  // Function to be called from loop()
  virtual void loop() override {
    encoder.loop(); // Reads pins values and calls callback funcitons
  }

  // Function that is called when knob is turned clockwise
  static void onTurnClockwise(void* self) {
    // Callback function is unaware of the pointer type so we cast it to current object type.
    auto& logic{*static_cast<RotaryEncoderLogic*>(self)};
    logic.counter++;
    Serial.print("Turn clockwise : ");
    Serial.println(logic.counter);
  }

  // Function that is called when knob is turned counter clockwise
  static void onTurnCounterClockwise(void* self) {
    auto& logic{*static_cast<RotaryEncoderLogic*>(self)};
    logic.counter--;
    Serial.print("Turn counter clockwise : ");
    Serial.println(logic.counter);
  }

  // Function that is called when putton is pushed
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

// Instantiating the object
RotaryEncoderLogic logic{};

void setup() {
  Serial.begin(57600);
  logic.begin();
}

void loop() {
  logic.loop();
  delay(5);
}
