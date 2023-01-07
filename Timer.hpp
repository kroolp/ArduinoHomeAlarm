// Timer.hpp
#ifndef TIMER
#define TIMER

#include "Arduino.h"

class Timer {
public:

  Timer();
  unsigned long reset();
  bool verifyInterval(int interval);

private:

  unsigned long time;
};

#endif