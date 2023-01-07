// HomeAlarm.hpp
#ifndef HOME_ALARM
#define HOME_ALARM

#include <Arduino.h>
#include "Pins.hpp"
#include "KeyController.hpp"
#include "LedLine.hpp"

class HomeAlarm {
public:

  HomeAlarm(const Pins& pins)
  : keyController(pins.keyPadRowPins, pins.keyPadColPins, pins.irReciverPin)
  , ledLine(pins.ledLinePin) {}

  void begin() {
    keyController.begin();
    ledLine.begin();
  }

  void execute() {
    char key = keyController.getKey();

    if (key)
      Serial.println(key);

    ledLine.blinkALL(LedLine::BLUE, LedLine::GREEN, 500);
  }

  private:

  KeyController keyController;
  LedLine ledLine;
};

#endif