#ifndef DISPLAYMANAGER_HPP
#define DISPLAYMANAGER_HPP

#include <SDL2/SDL_image.h>
#include <string>


class DisplayManager {
public:
  static bool isFirstRender();
  static SDL_Renderer* getRenderer();
  static void setRenderer(SDL_Renderer* renderer);
  static void setFirstRender(bool firstRender);
  static void clearScreen();
  static void presentScreen();
  static void drawRect(double x, double y, double w, double h, SDL_Color color);
  static SDL_Texture* makeTexture(std::string path);

  static const SDL_Color RED;
  static const SDL_Color BLUE;
  static const SDL_Color LIGHT_BLUE;
  static const SDL_Color YELLOW;
  static const SDL_Color ORANGE;
  static const SDL_Color PURPLE;
  static const SDL_Color GREEN;
  static const SDL_Color WHITE;
  static const SDL_Color BLACK;
  static const SDL_Color GRAY;
private:
  static bool firstRender;
  static SDL_Renderer* renderer;

};
#endif
