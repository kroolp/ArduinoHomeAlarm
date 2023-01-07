#include "TaskManager.hpp"

TaskManager::TaskManager(byte _size)
  : size(_size),
    tasks(new byte(size)) {
  reset();
}

bool TaskManager::isDone(byte index) {
  return tasks[index] == TASK_FINISHED;
}

bool TaskManager::isNotDone(byte index) {
  return !isDone(index);
}

byte TaskManager::setState(byte index, byte result) {
  return tasks[index] = result;
}

void TaskManager::reset() {
  for (int i = 0; i < size; i++)
    tasks[i] = TASK_NOT_FINISHED;
}