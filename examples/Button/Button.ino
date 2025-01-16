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

// This example demonstrates how to work with Button object.
//
// Hardware:
// - Arduino
// - Button
//
// Setup:
// - Button is connected to D2

#include <Arduino.h>
#include <CppComponentsLibrary.h>

// Instantiate a hardware api object.
HwApiImpl hw_api{};

constexpr int BUTTON_PIN{2};

// Class is used to implement callbacks and store the internal state.
//
// Inheritance from Device class isn't necessary, but it provides default functions
// to be implemented to have a consistent API
class ButtonLogic : public Device {
public:
  ButtonLogic() : button{
    {BUTTON_PIN, true}, // Setting DT pin to PULL_UP mode
    hw_api, // Providing to button instance of HwApi to be used to setup pin and read pin value
    {onPushButton, this}, // Connecting button push event to callback function and this object
    {onReleaseButton, this}, // Connecting button release event to callback function and this object 
    }
  {
  }

  virtual ~ButtonLogic() override = default;

  // Function to be called from setup() 
  virtual void begin() override {
    button.begin(); // Initializes pin
  }

  // Function to be called from loop()
  virtual void loop() override {
    button.loop(); // Reads pin value and calls callback funcitons
  }

  // Function that is called when button is pushed
  static void onPushButton(void* self) {
    // Callback function is unaware of the pointer type so we cast it to current object type.
    auto& logic{*static_cast<ButtonLogic*>(self)};
    logic.counter++;
    Serial.print("Button pushed : ");
    Serial.println(logic.counter);
  }

  // Function that is called when when button is released
  static void onReleaseButton(void* self) {
    auto& logic{*static_cast<ButtonLogic*>(self)};
    logic.counter--;
    Serial.print("Button released : ");
    Serial.println(logic.counter);
  }

private:
  Button button;
  int counter{0};
};

// Instantiating the object
ButtonLogic logic{};

void setup() {
  Serial.begin(57600);
  logic.begin();
}

void loop() {
  logic.loop();
  delay(10);
}
