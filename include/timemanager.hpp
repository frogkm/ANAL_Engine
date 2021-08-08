#ifndef TIMEMANAGER_HPP
#define TIMEMANAGER_HPP

#include <stdint.h>
#include "../include/timer.hpp"

class TimeManager {  //Class to handle global timers that many things need access to
public:
  void startTimingFrame();
  void doneTimingFrame();
  int getLastFrameDuration();  // Returns lastFrameDuration in ms

private:
  Timer frameTimer;
  uint32_t lastFrameDuration;



};

#endif
