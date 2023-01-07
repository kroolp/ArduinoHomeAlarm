// KeyController.hpp
#ifndef TASK_MANAGER
#define TASK_MANAGER

#define TASK_NOT_FINISHED 0
#define TASK_FINISHED 1

#include "Arduino.h"

class TaskManager {
  public:

  TaskManager(byte size);
  bool isDone(byte index);
  bool isNotDone(byte index);
  byte setState(byte index, byte result);
  void reset();

  private:

  byte *tasks;
  byte *size;
};

#endif