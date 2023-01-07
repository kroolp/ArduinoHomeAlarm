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
    : keyController(pins.keyPadRowPins, pins.keyPadColPins, pins.irReciverPin), ledLine(pins.ledLinePin) {}

  void begin() {
    keyController.begin();
    ledLine.begin();
  }

  void execute() {
    switch (state) {
      case StandBy:
        standBy();
        break;
      case StartingAlarm:
        startingAlarm();
        break;
      case Monitoring:
        monitoring();
        break;
      case Unlock:
        // unlock();
        break;
      case Alarm:
        // alarm();
        break;
    }
  }

private:

  void standBy() {
    char key = keyController.getKey();

    if (!tasks[0])
      tasks[0] = ledLine.setAllLed(LedLine::GREEN);

    if (key == 'A') {
      resetTasks();
      state = StartingAlarm;
    }
  }

  void startingAlarm() {
    if (!tasks[0])
      tasks[0] = ledLine.setAllLed(LedLine::BLUE, 750);
    else if (!tasks[1])
      tasks[1] = ledLine.setAllLed(LedLine::RED, 750);
    else {
      ledLine.clear();
      resetTasks();
      state = Monitoring;
    }
  }

  void monitoring() {
    ledLine.blink(7, LedLine::RED, LedLine::NO_COLOR, 500);

  // if (digitalRead(CONTACTRON_PIN) == HIGH) {
  //   state = 3;
  // } else if (digitalRead(PIR_PIN) == HIGH) {
  //   state = 4;
  // }
  }

  void resetTasks() {
    for (int i = 0; i < 2; i++)
      tasks[i] = 0;
  }

  KeyController keyController;
  LedLine ledLine;
  enum State { StandBy,
               StartingAlarm,
               Monitoring,
               Unlock,
               Alarm };
  State state = StandBy;
  int tasks[2] = { 0, 0 };
};

#endif