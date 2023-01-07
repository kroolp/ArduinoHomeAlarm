#include "src/HomeAlarm.hpp"

byte keyPadRowPins[4] = { 5, 4, 3, 2 };
byte keyPadColPins[4] = { 6, 7, 8, 9 };

Pins pins = {
  .keyPadRowPins = keyPadRowPins,
  .keyPadColPins = keyPadColPins,
  .irReciverPin = A3,
  .ledLinePin = A0,
  .contactronPin = A1,
  .pirPin = A2
};

String password = "1989";
String emergencyPassword = "1993";

HomeAlarm homeAlarm(pins, password, emergencyPassword);

void setup() {
  Serial.begin(9600);
  homeAlarm.begin();
}

void loop() {
  homeAlarm.execute();
}
