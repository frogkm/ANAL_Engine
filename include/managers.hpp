#ifndef MANAGERS_HPP
#define MANAGERS_HPP

class GameManager;
class DisplayManager;
class TimeManager;
class PhysicsManager;

class Managers {
public:
  static void setupManagers(int sW, int sH);
  static GameManager* gameManager;        //GameObject handling
  static DisplayManager* displayManager;  //Rendering functions
  static TimeManager* timeManager;  //Timing functions
  static PhysicsManager* physicsManager;
  static void cleanup();
  //PhysicsManager* physicsManager;  //Physics system
  //TimeManager* timeManager;       //Keep time
};
#endif
