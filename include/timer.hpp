
#ifndef TIMER_HPP
#define TIMER_HPP
#include <stdint.h>

class Timer {
public:
  Timer();
  void start();
  void stop();
  void pause();
  void unpause();
  uint32_t getTicks();
  bool isStarted();
  bool isPaused();

private:
  uint32_t startTime;
  uint32_t pauseTime;
  bool paused;
  bool started;
};

#endif
