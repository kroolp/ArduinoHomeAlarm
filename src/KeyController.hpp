// KeyController.hpp
#ifndef KEY_CONTROLLER
#define KEY_CONTROLLER

#include <Arduino.h>
#include <IRremote.h>
#include <Keypad.h>

class KeyController {
public:

  KeyController(byte keyPadRowPins[4], byte keyPadColPins[4], uint_fast8_t irReciverPin)
    : keyPad(makeKeymap(KEY_PAD_KEYS), keyPadRowPins, keyPadColPins, 4, 4),
      irReciver(irReciverPin) {}

  void begin() {
    irReciver.enableIRIn();
  }

  char getKey() {
    char key = keyPad.getKey();

    if(key)
      return key;

    if (irReciver.decode()) {
      IRData data = irReciver.decodedIRData;

      if (data.decodedRawData != 0 && data.protocol == 8 && data.address == 2) {
        key = decodeRemoteKey(data.command);
      }
      irReciver.resume();
    }

    return key;
  }

  String getKeys() {
    char key = getKey();
    
    if(key)
      if(key == 'A') {
        String temp = str;
        str = "";
        return temp;
      }
      else {
        str += String(key);
      }

    return "";
  }

private:

  char decodeRemoteKey(int command) {
    for (int i = 0; i < 10; i++)
      if (REMOTE_KEYS[i] == command)
        return REMOTE_KEY_VALUES[i];

    return 0;
  }

  Keypad keyPad;
  IRrecv irReciver;
  static const int REMOTE_KEYS[10];
  static const char REMOTE_KEY_VALUES[10];
  static const char KEY_PAD_KEYS[4][4];
  String str = "";
};

const int KeyController::REMOTE_KEYS[10] = { 0, 4, 6, 8, 10, 12, 14, 16, 18, 20 };
const char KeyController::REMOTE_KEY_VALUES[10] = { 'A', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
const char KeyController::KEY_PAD_KEYS[4][4] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

#endif