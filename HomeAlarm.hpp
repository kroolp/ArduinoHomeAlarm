#ifndef HOME_ALARM
#define HOME_ALARM

#include <Arduino.h>
#include "Pins.hpp"
#include "KeyController.hpp"
#include "LedLine.hpp"
#include "TaskManager.hpp"
#include "Timer.hpp"

class HomeAlarm {
public:

  HomeAlarm(const Pins& _pins, String _password, String _emergencyPassword)
    : pins(_pins),
      password(_password),
      emergencyPassword(_emergencyPassword),
      keyController(_pins.keyPadRowPins, _pins.keyPadColPins, _pins.irReciverPin),
      ledLine(_pins.ledLinePin) {}

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
        unlock();
        break;
      case Alarm:
        alarm();
        break;
    }
  }

private:

  void standBy() {
    char key = keyController.getKey();

    if (tasks.isNotDone(0))
      tasks.setState(0, ledLine.setAllLed(LedLine::GREEN));

    if (key == 'A') {
      tasks.reset();
      state = StartingAlarm;
    }
  }

  void startingAlarm() {
    if (tasks.isNotDone(0))
      tasks.setState(0, ledLine.setAllLed(LedLine::BLUE, 750));
    else if (tasks.isNotDone(1))
      tasks.setState(1, ledLine.setAllLed(LedLine::RED, 750));
    else if (tasks.isNotDone(2)) {
      timer.reset();
      tasks.setState(2, TASK_FINISHED);
    } else if (timer.verifyInterval(750)) {
      ledLine.clear();
      tasks.reset();
      state = Monitoring;
    }
  }

  void monitoring() {
    ledLine.blink(7, LedLine::RED, LedLine::NO_COLOR, 500);

    if (digitalRead(pins.contactronPin) == HIGH) {
      timer.reset();
      state = Unlock;
    } else if (digitalRead(pins.pirPin) == HIGH)
      state = Alarm;
  }

  void unlock() {
    String receivedPassword = keyController.getKeys();

    if(receivedPassword == password)
      state = StandBy;

    if (timer.verifyInterval(10000))
      state = Alarm;
  }

  void alarm() {
    ledLine.blinkALL(LedLine::RED, LedLine::BLUE, 100);

    String receivedPassword = keyController.getKeys();

    if(receivedPassword == emergencyPassword)
      state = StandBy;
  }

  KeyController keyController;
  LedLine ledLine;
  const Pins& pins;
  enum State { StandBy,
               StartingAlarm,
               Monitoring,
               Unlock,
               Alarm };
  State state = StandBy;
  TaskManager tasks = TaskManager(3);
  Timer timer;
  String password;
  String emergencyPassword;
};

#endif