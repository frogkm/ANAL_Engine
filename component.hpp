
#ifndef COMPONENT_HPP
#define COMPONENT_HPP
#include <vector>
#include <string>
#include <SDL2/SDL_image.h>
#include "Physics/particle.hpp"

class GameObject;

class Component {
public:
  virtual void update() = 0;  //Update called every game update
  virtual void start() = 0;   //Start called once at beginning of program.  Use to set pointers to other components.
  Component* getComponent(std::string tag);
  void setGameObject(GameObject* gameObject);
  std::string getTag();
protected:
  GameObject* gameObject;
  std::string tag;
};

class Transform : public Component {
public:
  Transform();
  Transform(double x, double y);
  void set(double x, double y);
  void move(double x_move, double y_move);
  double getX();
  double getY();
  void update();
  void start();
private:
  double x;
  double y;
};

class RigidBody : public Component {
public:
  RigidBody();
  RigidBody(double dx, double dy, double ddx, double ddy, double mass, double angle);
  void update();
  void start();
  void addImpulse(double fx, double fy);
private:
  double dx;
  double dy;
  double ddx;
  double ddy;
  double mass;
  double angle;
  double dAngle;
  Transform* transform;
};

class Point : public Component {
public:
  Point();
  Point(double dx, double dy, double ddx, double ddy, double mass);
  void update();
  void start();
  Particle* getParticleAddress();
private:
  Transform* transform;
  Particle particle;
};

class BoxCollider : public Component {
public:
  BoxCollider(double w, double h);
  void update();
  void start();
private:
  double w;
  double h;
  Transform* transform;
};

class Renderer : public Component {
public:
  //Renderer();
  Renderer(std::string imgPath, double renderW, double renderH); //Works with pngs, jpegs, and possibly more!
  void update();
  void start();
  ~Renderer();
private:
  Transform* transform;
  SDL_Renderer* renderer;
  SDL_Texture* currentTexture;
  double renderW;
  double renderH;
};


#endif
