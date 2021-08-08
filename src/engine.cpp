#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "../include/engine.hpp"
#include "../include/gameobject.hpp"
#include "../include/component.hpp"
#include "../include/managers.hpp"
#include "../include/gamemanager.hpp"
#include "../include/displaymanager.hpp"
#include "../include/timemanager.hpp"
#include "../include/physicsmanager.hpp"
#include "../include/vector2.hpp"
#include "../include/particle.hpp"
#include "../include/force.hpp"


void Engine::loadGameObjects() {
  Managers::gameManager->addObj(new GameObject({new Transform(), new Renderer("resources/space.jpeg", Managers::displayManager->getsW(), Managers::displayManager->getsH())}));

  Point* point = new Point(0, 0, 0, 0, 1);
  ParticleForceGenerator* grav = new ConstantForceGenerator(Vector2(0, 100));
  Managers::physicsManager->addParticle(point->getParticleAddress(), grav);
  Vector2* anchor = new Vector2(200, 100);
  ParticleForceGenerator* spring = new SpringGenerator(anchor, 2, 100);
  Managers::physicsManager->addParticle(point->getParticleAddress(), spring);
  ParticleForceGenerator* damp = new DragGenerator(0.01, 0);
  Managers::physicsManager->addParticle(point->getParticleAddress(), damp);
	Managers::gameManager->addObj(new GameObject({new Transform(200, 200), new Renderer("resources/mouse.png", 50, 50), point}));
}

Engine::Engine(int sW, int sH, int fpsLimit) {
  initSDL();
  Managers::setupManagers(sW, sH);
}

Engine::~Engine() {
  Managers::cleanup();
}

void Engine::initSDL() {
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);
  TTF_Init();
}

void Engine::startGameObjects() {
  Managers::gameManager->start();
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

  Managers::physicsManager->updateForces(Managers::timeManager->getLastFrameDuration());
  Managers::gameManager->updateObjects();
  Managers::displayManager->clearScreen();
  Managers::gameManager->drawObjects();
  Managers::displayManager->presentScreen();

}

void Engine::startGameLoop() {
	SDL_Event event;
  bool quit = false;
	while(!quit){
    Managers::timeManager->startTimingFrame();  //Time the entire frame
    //Code before everything
    quit = innerLoop(event);
    //Code after everything
    Managers::timeManager->doneTimingFrame();  //Record the frame's duration
  }
}
