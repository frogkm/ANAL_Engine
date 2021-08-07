#include <vector>
#include <iostream>
#include <sstream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "gameobject.hpp"
#include "component.hpp"
#include "gamemanager.hpp"
#include "displaymanager.hpp"
#include "timer.hpp"
#include "globals.hpp"
#include "Physics/force.hpp"

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500
#define SCREEN_FPS 60
#define SCREEN_TICKS_PER_FRAME 1000 / SCREEN_FPS


#define GRID_ON 1
#define GRID_SIZE 50

void loadMedia();
void init();
void update();
void close();
void loadGameObjects();
void start();
void drawGrid();

int lastFrameTime = 30;  //default rand num
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;
ParticleForceRegistry registry;

int main(int argc, char* args[]) {
	init();
	loadMedia();
  loadGameObjects();
	start();

	SDL_Color timerColor = {255, 255, 255, 255};
	Timer fpsTimer;
	Timer capTimer;
	std::stringstream timerText;
	int countedFrames = 0;
  fpsTimer.start();

	SDL_Event event;
  bool quit = false;
	while(!quit) {
		capTimer.start();
		while(SDL_PollEvent(&event) != 0) {
			if(event.type == SDL_QUIT) {
				quit = true;
			}
		}
		update();

		float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
    if(avgFPS > 2000000) {
    	avgFPS = 0;
    }
    timerText.str("");
    timerText << "FPS: " << avgFPS;
	  SDL_Surface* fpsSurf = TTF_RenderText_Solid(font, timerText.str().c_str(), timerColor);
	  SDL_Texture* fpsTexture = SDL_CreateTextureFromSurface(renderer, fpsSurf);
	  SDL_Rect textRect;
	  textRect.x = 0;
	  textRect.y = 0;
	  textRect.w = 200;
	  textRect.h = 100;
	  SDL_RenderCopy(renderer, fpsTexture, NULL, &textRect);
	  SDL_FreeSurface(fpsSurf);
	  SDL_DestroyTexture(fpsTexture);
    SDL_RenderPresent(renderer);
		countedFrames++;

		//If frame finished early
    int frameTicks = capTimer.getTicks();
    if(frameTicks < SCREEN_TICKS_PER_FRAME)
    {
        //Wait remaining time
        SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
    }
		lastFrameTime = (int)capTimer.getTicks();
	}
	close();
	return 0;
}

//Main update function
void update() {
	registry.updateForces(lastFrameTime / 1000.f);
	GameManager::update();
  if (GRID_ON) {
  	drawGrid();
  }
	DisplayManager::presentScreen();
}


void start() {
	for (GameObject* obj : GameManager::getObjs()) {
    obj->start();
  }
}

void drawGrid() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	for (int i = 0; i < (int)(SCREEN_HEIGHT / GRID_SIZE); i ++){
		SDL_RenderDrawLine(renderer, 0, i * GRID_SIZE, SCREEN_WIDTH, i * GRID_SIZE);
	}
	for (int j = 0; j < (int)(SCREEN_WIDTH / GRID_SIZE); j ++){
		SDL_RenderDrawLine(renderer, j * GRID_SIZE, 0, j * GRID_SIZE, SCREEN_HEIGHT);
	}
}

void loadMedia() {
	font = TTF_OpenFont("font.ttf", 24);
}

void init() {
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);
  TTF_Init();
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

  window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);
	DisplayManager::setRenderer(renderer);

}
void close() {
	for (GameObject* obj : GameManager::getObjs()) {
    delete obj;
  }
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;

	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

void loadGameObjects(){

	GameManager::addObj(new GameObject({new Transform(), new Renderer("space.jpeg", SCREEN_WIDTH, SCREEN_HEIGHT)}));
	//GameManager::addObj(new GameObject({new Transform(), new Renderer("rat.png", 50, 200)}));
	//GameManager::addObj(new GameObject({new Transform(), new Renderer("mouse.png", 100, 100), new RigidBody(0.1, 0.1, 0.001, 0, 1)}));
	//GameManager::addObj(new GameObject({new Transform(200, 200), new Renderer("bunny.png", 100, 100), new RigidBody(-0.5, 0.1, 0.001, 0, 1)}));
	//GameManager::addObj(new GameObject({new Transform(), new Renderer("mouse.png", 100, 100), new RigidBody(0, 0, 0, 10, 1, 0)}));
	Point* point = new Point(0, 0, 0, 0, 1);
	Vector2 gravity(0, 100);
	Vector2* anchorPt = new Vector2(200, 100);
	ParticleForceGenerator* gravGen = new ConstantForceGenerator(gravity);
	ParticleForceGenerator* springGen = new SpringGenerator(anchorPt, 2, 100);
	registry.add(point->getParticleAddress(), gravGen);
	registry.add(point->getParticleAddress(), springGen);
	GameManager::addObj(new GameObject({new Transform(200, 200), new Renderer("mouse.png", 50, 50), point}));




}
