#include <string>
#include <iostream>
#include "component.hpp"
#include "gameobject.hpp"
//#include <SDL2/SDL_image.h>
#include "displaymanager.hpp"


Component* Component::getComponent(std::string tag) {
  return gameObject->getComponent(tag);
}

void Component::setGameObject(GameObject* gameObject) {
  this->gameObject = gameObject;
}

std::string Component::getTag() {
  return tag;
}

void Transform::update() {}

Transform::Transform() {
  tag = "Transform";
  x = 0;
  y = 0;
}

Transform::Transform(double x, double y) {
  tag = "Transform";
  this->x = x;
  this->y = y;
}

void Transform::set(double x, double y) {
  this->x = x;
  this->y = y;
}
void Transform::move(double x_move, double y_move) {
  x += x_move;
  y += y_move;
}
double Transform::getX() {
  return x;
}
double Transform::getY() {
  return y;
}
void Transform::start() {}

RigidBody::RigidBody() {
  tag = "RigidBody";
  dx = 0;
  dy = 0;
  ddx = 0;
  ddy = 0;
  mass = 1;
}

RigidBody::RigidBody(double dx, double dy, double ddx, double ddy, double mass, double angle) {
  tag = "RigidBody";
  this->dx = dx;
  this->dy = dy;
  this->ddx = ddx;
  this->ddy = ddy;
  this->mass = mass;
  this->angle = angle;
}

void RigidBody::update() {
  dx += ddx; // add the constant forces
  dy += ddy; // add the sonstant forces -- only for things that never change like gravity or some sort of magnet
  transform->move(dx, dy);

}

void RigidBody::addImpulse(double fx, double fy) {
  dx += fx / mass; //Impulse creates a force that lasts one frame -- so we just add the acceleration straight to the velocities
  dy += fy / mass;
}

void RigidBody::start() {
  transform = (Transform*)getComponent("Transform");
}


BoxCollider::BoxCollider(double w, double h) {
  this->w = w;
  this->h = h;
}
void BoxCollider::update() {

}
void BoxCollider::start() {
  transform = (Transform*)getComponent("Transform");
}





//Renderer::Renderer() {
//  tag = "Renderer";
//}

Renderer::Renderer(std::string imgPath, double renderW, double renderH) {
  tag = "Renderer";
  currentTexture = DisplayManager::makeTexture(imgPath);
  this->renderW = renderW;
  this->renderH = renderH;
}

Renderer::~Renderer() {
  if (currentTexture != NULL) {
    SDL_DestroyTexture(currentTexture);
  }
}

void Renderer::update() {
  //Clears screen if this is the first obj to render
  if (DisplayManager::isFirstRender()) {
    DisplayManager::setFirstRender(false);
    DisplayManager::clearScreen();
  }
  //DisplayManager::drawRect(transform->getX(), transform->getY(), 100, 100, DisplayManager::RED);

  SDL_Rect dest;

  dest.x = transform->getX();
  dest.y = transform->getY();
  dest.w = renderW;
  dest.h = renderH;
  SDL_RenderCopy(DisplayManager::getRenderer(), currentTexture, NULL, &dest);
}

void Renderer::start() {
  transform = (Transform*)getComponent("Transform");
}
