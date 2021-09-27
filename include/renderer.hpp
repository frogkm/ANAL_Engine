#ifndef RENDERER_HPP
#define RENDERER_HPP
//#include <vector>
//#include <string>
#include <SDL2/SDL_image.h>
#include "component.hpp"

class RigidBody;


class RectRenderer : public Component {
public:
  RectRenderer(SDL_Color color, double renderW, double renderH); //Works with pngs, jpegs, and possibly more!
  void update();
  void start();
  void draw();
private:
  Transform* transform;
  double renderW;
  double renderH;
  SDL_Color color;
};


class Renderer : public Component {
public:
  Renderer(std::string imgPath, double renderW, double renderH); //Works with pngs, jpegs, and possibly more!
  void update();
  void start();
  void draw();
  ~Renderer();
private:
  Transform* transform;
  SDL_Texture* currentTexture;
  double renderW;
  double renderH;
};

class SpriteRenderer : public Component {
public:
  SpriteRenderer(std::string imgPath, double renderW, double renderH); //Works with pngs, jpegs, and possibly more!
  void update();
  void start();
  void draw();
  ~SpriteRenderer();
private:
  Transform* transform;
  RigidBody* rigidBody;
  SDL_Texture* currentTexture;
  double renderW;
  double renderH;
};




#endif
