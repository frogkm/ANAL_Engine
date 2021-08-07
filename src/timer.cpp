#include <SDL2/SDL.h>
#include "../include/timer.hpp"

Timer::Timer() {
    startTime = 0;
    pauseTime = 0;
    paused = false;
    started = false;
}

void Timer::start() {
    started = true;
    paused = false;
    startTime = SDL_GetTicks();
	  pauseTime = 0;
}

void Timer::stop() {
    started = false;
    paused = false;
    startTime = 0;
  	pauseTime = 0;
}

void Timer::pause() {
    if(started && !paused) {
        paused = true;
        pauseTime = SDL_GetTicks() - startTime;
		    startTime = 0;
    }
}

void Timer::unpause() {
    if(started && paused) {
        paused = false;
        startTime = SDL_GetTicks() - pauseTime;
        pauseTime = 0;
    }
}

uint32_t Timer::getTicks() {
  if(started) {
      if(paused) {
          return pauseTime;
      }
      else {
          return (SDL_GetTicks() - startTime);
      }
  }
  return 0;
}

bool Timer::isStarted()
{
    return started;
}

bool Timer::isPaused()
{
    return paused && started;
}
