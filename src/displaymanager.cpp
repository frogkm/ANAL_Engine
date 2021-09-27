#include "../include/displaymanager.hpp"

const SDL_Color DisplayManager::RED = {255, 0, 0};
const SDL_Color DisplayManager::BLUE = {0, 0, 255};
const SDL_Color DisplayManager::LIGHT_BLUE = {0, 255, 255};
const SDL_Color DisplayManager::YELLOW = {255, 255, 0};
const SDL_Color DisplayManager::ORANGE = {255, 128, 0};
const SDL_Color DisplayManager::PURPLE = {128, 0, 255};
const SDL_Color DisplayManager::GREEN = {0, 255, 0};
const SDL_Color DisplayManager::WHITE = {255, 255, 255};
const SDL_Color DisplayManager::BLACK = {0, 0, 0};
const SDL_Color DisplayManager::GRAY = {100, 100, 100};

//SDL_Renderer* DisplayManager::renderer = NULL;
//SDL_Window* DisplayManager::window = NULL;

DisplayManager::DisplayManager(int sW, int sH) {
  this->sW = sW;
  this->sH = sH;
  window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, sW, sH, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

DisplayManager::~DisplayManager() {
  SDL_DestroyRenderer(renderer);
  renderer = NULL;
  SDL_DestroyWindow(window);
  window = NULL;
}

int DisplayManager::getsW() {
  return sW;
}

int DisplayManager::getsH() {
  return sH;
}


SDL_Renderer* DisplayManager::getRenderer() {
  return renderer;
}

void DisplayManager::setRenderer(SDL_Renderer* renderer) {
  this->renderer = renderer;
}

void DisplayManager::clearScreen() {
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(renderer);
}
/* //allow for color parameter for clearing
void DisplayManager::clearScreen(COLOR) {
  SDL_SetRenderDrawColor(DisplayManager::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(DisplayManager::renderer);
}
*/

//Draws a rect centered at x, y
void DisplayManager::drawRect(double x, double y, double w, double h, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_Rect temp;
	temp.x = x - w / 2;
	temp.y = y - h / 2;
	temp.w = w;
	temp.h = h;
	SDL_RenderFillRect(renderer, &temp);
}

void DisplayManager::drawTexture(double x, double y, double w, double h, SDL_Texture* texture) {
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  dest.w = w;
  dest.h = h;
  SDL_RenderCopy(renderer, texture, NULL, &dest);
}
/*
void DisplayManager::drawTexture(double x, double y, double w, double h, SDL_Texture* texture, double angle) {
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  dest.w = w;
  dest.h = h;
  SDL_RenderCopy(renderer, texture, NULL, &dest);
}
*/

void DisplayManager::presentScreen() {
  SDL_RenderPresent(renderer);
}

SDL_Texture* DisplayManager::makeTexture(std::string path) {
  SDL_Surface* surface = IMG_Load(path.c_str());
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  return texture;
}
