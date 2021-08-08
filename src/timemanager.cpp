#include "../include/timemanager.hpp"

void TimeManager::startTimingFrame() {
  frameTimer.start();
}
void TimeManager::doneTimingFrame() {
  lastFrameDuration = frameTimer.getTicks();
}
int TimeManager::getLastFrameDuration() {
  return ((int) lastFrameDuration);
}
