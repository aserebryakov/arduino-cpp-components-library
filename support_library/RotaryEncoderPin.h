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

#ifndef ROTARYENCODERPINIMPL_H
#define ROTARYENCODERPINIMPL_H

#include "HwApi.h"

enum class PIN_CHANGE {
  LOW_HIGH,
  HIGH_LOW,
  NONE
};

class RotaryEncoderPin {
public:
  RotaryEncoderPin(const int pin_number, HwApi& hwapi);
  ~RotaryEncoderPin() = default;
  virtual PIN_CHANGE readPinChange();
  virtual bool readPinStatus();

private:
  void readPin();
  
  int pin_number;
  HwApi& hw_api;
  bool current_state{false};
  bool previous_state{false};
};

#endif //ROTARYENCODERPINIMPL_H
