// MIT License
//
// Copyright (c) 2024 Alexander Serebryakov
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

#include "RotaryEncoderPinImpl.h"
#include "Arduino.h"

RotaryEncoderPinImpl::RotaryEncoderPinImpl(const int pin_number) : pin_number{pin_number} {
};

PIN_CHANGE RotaryEncoderPinImpl::readPinChange() {
  readPin();

  if (previous_state == current_state) {
    return PIN_CHANGE::NONE;
  }

  if (previous_state == true && current_state == false) {
    return PIN_CHANGE::HIGH_LOW;
  }

  return PIN_CHANGE::LOW_HIGH;
}

void RotaryEncoderPinImpl::readPin() {
  previous_state = current_state;
  current_state = digitalRead(pin_number) == HIGH;
}

bool RotaryEncoderPinImpl::readPinStatus() {
  readPin();
  return current_state;
}