#ifndef COMPONENT_HPP
#define COMPONENT_HPP
#include <vector>
#include <string>
#include <SDL2/SDL_image.h>
#include "vector2.hpp"


class GameObject;
class DisplayManager;


class Component {
public:
  virtual void update() = 0;  //Update called every game update
  virtual void draw();  //Draw called every game update
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
  Vector2& getPosition();
  void update();
  void start();
private:
  Vector2 position;
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


#endif
