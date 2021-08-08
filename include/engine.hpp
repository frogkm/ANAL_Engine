#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <SDL2/SDL.h>

class GameManager;
class DisplayManager;

class Engine {
public:
  Engine(int sW, int sH, int fpsLimit);  //Instantiate all managers
  ~Engine();  //Cleanup
  void start();  //Start the engine
  void initSDL();
  void init();
  void loadGameObjects();
  void stop();
  void startGameObjects();
  void startGameLoop();  //Main game loop
  bool innerLoop(SDL_Event &event);  //This method called every frame
private:
  GameManager* gameManager;        //GameObject handling
  DisplayManager* displayManager;  //Rendering functions
  //PhysicsManager* physicsManager;  //Physics system
  //TimeManager* timeManager;       //Keep time
};
#endif
