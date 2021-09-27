#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "../include/engine.hpp"
#include "../include/gameobject.hpp"
#include "../include/component.hpp"
#include "../include/renderer.hpp"
#include "../include/managers.hpp"
#include "../include/gamemanager.hpp"
#include "../include/displaymanager.hpp"
#include "../include/timemanager.hpp"
#include "../include/physicsmanager.hpp"
#include "../include/vector2.hpp"
#include "../include/particle.hpp"
#include "../include/force.hpp"


void Engine::loadGameObjects() {
  Particle* particle = new Particle();
  Vector2* anchor = new Vector2(200, 100);

  ParticleForceGenerator* grav = new ConstantForceGenerator(Vector2(0, 100));
  ParticleForceGenerator* spring = new SpringGenerator(anchor, 2, 100);
  ParticleForceGenerator* damp = new DragGenerator(0.01, 0);

  Managers::physicsManager->addParticle(particle, grav); //Apply gravity to particle component
  Managers::physicsManager->addParticle(particle, spring); //Apply spring to particle from the anchor
  Managers::physicsManager->addParticle(particle, damp); //Apply damping to particle

  Managers::gameManager->addObj(new GameObject({new Transform(), new Renderer("resources/space.jpeg", Managers::displayManager->getsW(), Managers::displayManager->getsH())})); //Add a static background
	Managers::gameManager->addObj(new GameObject({new Transform(200, 200), new Renderer("resources/mouse.png", 50, 50), particle}));  //Add basic components and particle to object, and add object to the scene
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
