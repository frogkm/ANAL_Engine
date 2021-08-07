#include <string>
#include <iostream>
#include "../include/gameobject.hpp"

GameObject::GameObject() {
  //std::vector<Component> components;
}

GameObject::GameObject(std::vector<Component*> components) {
  for (Component* comp : components) {
    addComponent(comp);
  }
}

void GameObject::update() {
  for (Component* comp : components) {
    comp->update();
  }
}

void GameObject::start() {
  for (Component* comp : components) {
    comp->start();
  }
}

Component* GameObject::getComponent(std::string tag) {
  for (Component* comp : components) {
    if (comp->getTag() == tag) {
      return comp;
    }
  }
}

std::vector<Component*> GameObject::getComponents() {
  return components;
}

void GameObject::addComponent(Component* comp) {
  comp->setGameObject(this);
  components.push_back(comp);
}

GameObject::~GameObject() {
  for (int i = 0; i < components.size(); i++) {
    delete components[i];
  }
}
