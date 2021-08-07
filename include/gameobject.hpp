#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include <vector>
#include <string>
//#include <unordered_map>
#include "component.hpp"

class GameObject {
public:
  GameObject();
  GameObject(std::vector<Component*> components);
  void update();
  void start();
  Component* getComponent(std::string tag);
  std::vector<Component*> getComponents();
  void addComponent(Component* comp);
  ~GameObject();
private:
  std::vector<Component*> components;
  //std:unordered_map<string, Component*> components;
};
#endif
