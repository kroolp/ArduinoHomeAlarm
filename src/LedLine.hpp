// LedLine.hpp
#ifndef LED_LINE
#define LED_LINE

#include <Adafruit_NeoPixel.h>
#include "Arduino.h"
#include "TaskManager.hpp"
#include "Timer.hpp"

class LedLine {
public:

  LedLine(int ledLinePin)
    : ledLine(8, ledLinePin, NEO_GRB + NEO_KHZ800) {}

  void begin() {
    ledLine.begin();
    ledLine.clear();
    ledLine.show();
  }

  int setAllLed(int color[], int interval = 0) {
    if (!timer.verifyInterval(interval))
      return TASK_NOT_FINISHED;

    ledLine.setPixelColor(currentLedIndex, ledLine.Color(color[0], color[1], color[2]));
    ledLine.show();

    if (currentLedIndex >= 7) {
      currentLedIndex = 0;
      return TASK_FINISHED;
    } else {
      currentLedIndex++;
      return TASK_NOT_FINISHED;
    }
  }

  void blink(int index, int color1[], int color2[], int interval) {
    if (!timer.verifyInterval(interval))
      return;

    int* color;

    if (!equalColor(color1, currentColor)) {
      color = color1;
    } else {
      color = color2;
    }

    ledLine.setPixelColor(index, ledLine.Color(color[0], color[1], color[2]));
    ledLine.show();

    currentColor = color;
  }

  void blinkALL(int color1[], int color2[], int interval) {
    if (!timer.verifyInterval(interval))
      return;

    int* color;

    if (!equalColor(color1, currentColor)) {
      color = color1;
    } else {
      color = color2;
    }

    for (int i = 0; i < 8; i++)
      ledLine.setPixelColor(i, ledLine.Color(color[0], color[1], color[2]));

    ledLine.show();

    currentColor = color;
  }

  void clear() {
    ledLine.clear();
    ledLine.show();
  }

  static const int RED[3];
  static const int STRONG_RED[3];
  static const int GREEN[3];
  static const int BLUE[3];
  static const int STRONG_BLUE[3];
  static const int NO_COLOR[3];

private:

  bool equalColor(int color1[], int color2[]) {
    for (int i = 0; i < 3; i++)
      if (color1[i] != color2[i])
        return false;

    return true;
  }

  Adafruit_NeoPixel ledLine;
  int* currentColor;
  int currentLedIndex = 0;
  Timer timer;
};

const int LedLine::RED[3] = { 15, 0, 0 };
const int LedLine::STRONG_RED[3] = { 255, 0, 0 };
const int LedLine::GREEN[3] = { 0, 15, 0 };
const int LedLine::BLUE[3] = { 0, 0, 15 };
const int LedLine::STRONG_BLUE[3] = { 0, 0, 255 };
const int LedLine::NO_COLOR[3] = { 0, 0, 0 };

#endif