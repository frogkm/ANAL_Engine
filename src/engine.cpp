#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>


#include "../include/engine.hpp"
#include "../include/gamemanager.hpp"
#include "../include/displaymanager.hpp"
#include "../include/gameobject.hpp"
#include "../include/component.hpp"
//#include "../include/physicsmanager.hpp"
//#include "../include/timemanager.hpp"


//Engine::physicsManager = NULL;
//Engine::timeManager = NULL;

void Engine::loadGameObjects() {
  gameManager->addObj(new GameObject({new Transform(), new Renderer(displayManager, "resources/space.jpeg", displayManager->getsW(), displayManager->getsH())}));
	gameManager->addObj(new GameObject({new Transform(200, 200), new Renderer(displayManager, "resources/mouse.png", 50, 50)}));
}

Engine::Engine(int sW, int sH, int fpsLimit) {
  initSDL();
  gameManager = new GameManager();
  displayManager = new DisplayManager(sW, sH);
  //physicsManager = new PhysicsManager();
  //timeManager = new TimeManager();
}

Engine::~Engine() {
  delete gameManager;
  delete displayManager;
  //delete physicsManager;
  //delete timeManager;
  gameManager = NULL;
  displayManager = NULL;
  //physicsManager = NULL;
  //timeManager = NULL;
}

void Engine::initSDL() {
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);
  TTF_Init();
}

void Engine::startGameObjects() {
  gameManager->start();
}

void Engine::start() {
  loadGameObjects();
  startGameObjects();
  startGameLoop();
}

void Engine::stop() {
  //for (GameObject* obj : GameManager::getObjs()) {
  //  delete obj;
  //}
  IMG_Quit();
  SDL_Quit();
  TTF_Quit();
}

bool Engine::innerLoop(SDL_Event &event) {
  while(SDL_PollEvent(&event) != 0) {
    if(event.type == SDL_QUIT) {
      return true;
    }
  }

  gameManager->updateObjects();
  displayManager->clearScreen();
  gameManager->drawObjects();
  displayManager->presentScreen();
  //displayManager.drawObjects();


}

void Engine::startGameLoop() {
	SDL_Event event;
  bool quit = false;
	while(!quit){
    //Code before everything
    quit = innerLoop(event);
    //Code after everything
  }
}
