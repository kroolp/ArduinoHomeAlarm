// Pins.hpp
#ifndef PINS
#define PINS

#include <Arduino.h>

struct Pins {
  byte *keyPadRowPins;
  byte *keyPadColPins;
  byte irReciverPin;
  byte ledLinePin;
};


#endif