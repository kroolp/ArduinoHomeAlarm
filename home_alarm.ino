#include "KeyController.hpp"
#include "LedLine.hpp"

#define IR_RECIVER_PIN A3
#define LED_LINE_PIN A0

byte keyPadRowPins[4] = { 5, 4, 3, 2 };
byte keyPadColPins[4] = { 6, 7, 8, 9 };

KeyController keyController(keyPadRowPins, keyPadColPins, IR_RECIVER_PIN);
LedLine ledLine(LED_LINE_PIN);

void setup() {
  Serial.begin(9600);
  keyController.begin();
  ledLine.begin();
}

void loop() {
  char key = keyController.getKey();

  if(key)
    Serial.println(key);

  // ledLine.blinkALL(LedLine::BLUE, LedLine::GREEN, 500);
}
