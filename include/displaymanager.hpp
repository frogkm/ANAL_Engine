#ifndef DISPLAYMANAGER_HPP
#define DISPLAYMANAGER_HPP

#include <SDL2/SDL_image.h>
#include <string>


class DisplayManager {
public:
  DisplayManager(int sW, int sH);
  ~DisplayManager();
  SDL_Renderer* getRenderer();
  void setRenderer(SDL_Renderer* renderer);
  void clearScreen();
  void presentScreen();
  void drawRect(double x, double y, double w, double h, SDL_Color color);
  void drawTexture(double x, double y, double w, double h, SDL_Texture* texture);
  SDL_Texture* makeTexture(std::string path);
  int getsW();
  int getsH();

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
  SDL_Renderer* renderer;
  SDL_Window* window;
  int sW;
  int sH;

};
#endif
