#include "MIDIUSB.h"
#include "DigitalPin.h"
#include "HwApiImpl.h"

constexpr int NOTE_PIN{A0};
constexpr int BUTTON_PIN{14};
constexpr int LEGATO_PIN{10};

HwApiImpl hw_api{};
DigitalPin buttonPin{BUTTON_PIN, hw_api};
DigitalPin legatoButtonPin{LEGATO_PIN, hw_api};

// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LEGATO_PIN, INPUT_PULLUP);
}

// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

uint8_t read_note() {
  const int16_t pin_value{analogRead(NOTE_PIN)};
  constexpr int MIN_NOTE{36};
  constexpr int MAX_NOTE{72};
  const auto inverted_note{map(pin_value, 0, 1023, 0, MAX_NOTE - MIN_NOTE)};
  return MAX_NOTE - inverted_note;
}

void loop() {
  static auto previous_note{0};
  buttonPin.readPin();
  legatoButtonPin.readPin();

  if (buttonPin.getPinChange() == PIN_CHANGE::HIGH_LOW) {
    Serial.println("Sending note off");
    noteOff(0, previous_note, 64);

    auto current_note{read_note()};
    Serial.println("Sending note on");
    noteOn(0, current_note, 64);
    previous_note = current_note;
  }

  if (buttonPin.getPinChange() == PIN_CHANGE::LOW_HIGH) {
    Serial.println("Sending note off");
    noteOff(0, previous_note, 64);
  }

  if (legatoButtonPin.getPinChange() == PIN_CHANGE::HIGH_LOW) {
    Serial.println("Sending note off");
    noteOff(0, previous_note, 64);
    
    auto current_note{read_note()};
    Serial.println("Sending note on");
    noteOn(0, current_note, 64);
    previous_note = current_note;
  }

  if (!legatoButtonPin.getPinStatus()) {
    auto current_note{read_note()};

    if (current_note != previous_note) {
      Serial.println("Sending note off");
      noteOff(0, previous_note, 64);
      Serial.println("Sending note on");
      noteOn(0, current_note, 64);
      previous_note = current_note;
    }
  }

  if (legatoButtonPin.getPinChange() == PIN_CHANGE::LOW_HIGH) {
    Serial.println("Sending note off");
    noteOff(0, previous_note, 64);
  }

  MidiUSB.flush();

  delay(10);
}