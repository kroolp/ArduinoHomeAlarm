#include "Timer.hpp"

Timer::Timer() {
  reset();
}
unsigned long Timer::reset() {
  time = millis();
}
bool Timer::verifyInterval(int interval) {
  if (millis() - time > interval) {
    reset();
    return true;
  }

  return false;
}