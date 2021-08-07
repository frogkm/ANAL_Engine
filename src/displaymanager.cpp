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

bool DisplayManager::firstRender = true;
SDL_Renderer* DisplayManager::renderer = NULL;

bool DisplayManager::isFirstRender() {
  return firstRender;
}
SDL_Renderer* DisplayManager::getRenderer() {
  return renderer;
}

void DisplayManager::setRenderer(SDL_Renderer* renderer) {
  DisplayManager::renderer = renderer;
}

void DisplayManager::setFirstRender(bool firstRender) {
  DisplayManager::firstRender = firstRender;
}

void DisplayManager::clearScreen() {
  SDL_SetRenderDrawColor(DisplayManager::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(DisplayManager::renderer);
}
/* //allow for color parameter for clearing
void DisplayManager::clearScreen(COLOR) {
  SDL_SetRenderDrawColor(DisplayManager::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(DisplayManager::renderer);
}
*/

//Draws a rect centered at x, y
void DisplayManager::drawRect(double x, double y, double w, double h, SDL_Color color) {
  SDL_SetRenderDrawColor(DisplayManager::renderer, color.r, color.g, color.b, color.a);
	SDL_Rect temp;
	temp.x = x - w / 2;
	temp.y = y - h / 2;
	temp.w = w;
	temp.h = h;
	SDL_RenderFillRect(DisplayManager::renderer, &temp);
}

void DisplayManager::presentScreen() {
  SDL_RenderPresent(DisplayManager::renderer);
  DisplayManager::firstRender = true;
}

SDL_Texture* DisplayManager::makeTexture(std::string path) {
  SDL_Surface* surface = IMG_Load(path.c_str());
  SDL_Texture* texture = SDL_CreateTextureFromSurface(DisplayManager::renderer, surface);
  SDL_FreeSurface(surface);
  return texture;
}
