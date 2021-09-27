#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/component.hpp"
#include "../include/gameobject.hpp"
//#include <SDL2/SDL_image.h>
#include "../include/displaymanager.hpp"
#include "../include/vector2.hpp"
#include "../include/particle.hpp"
#include "../include/managers.hpp"
#include "../include/timemanager.hpp"


Component* Component::getComponent(std::string tag) {
  return gameObject->getComponent(tag);
}

void Component::setGameObject(GameObject* gameObject) {
  this->gameObject = gameObject;
}

std::string Component::getTag() {
  return tag;
}

void Component::draw() {}

void Transform::update() {}

Transform::Transform() {
  tag = "Transform";
  //position = Vector2(0, 0)
}

Transform::Transform(double x, double y) {
  tag = "Transform";
  position = Vector2(x, y);
}

void Transform::set(double x, double y) {
  position.set(x, y);
}
void Transform::move(double x_move, double y_move) {
  position += Vector2(x_move, y_move);
}
double Transform::getX() {
  return position.getX();
}
double Transform::getY() {
  return position.getY();
}
Vector2& Transform::getPosition() {
  return position;
}
void Transform::start() {}




BoxCollider::BoxCollider(double w, double h) {
  this->w = w;
  this->h = h;
}
void BoxCollider::update() {

}
void BoxCollider::start() {
  transform = (Transform*)getComponent("Transform");
}
