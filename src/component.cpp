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

/*
Point::Point() {
  tag = "Point";
  particle.setMass(1); //Can't leave mass at 0 by default...
}
Point::Point(double dx, double dy, double ddx, double ddy, double mass) {
  tag = "Point";
  particle.setVelocity(Vector2(dx, dy));
  particle.setAcceleration(Vector2(ddx, ddy));
  particle.setMass(mass);
}
void Point::update() {

  transform->set(particle.getPosition().getX(), particle.getPosition().getY());
  particle.integrate(Managers::timeManager->getLastFrameDuration() / 1000.f);  //integrate using previous frame as an estimate

}
void Point::start() {
  transform = (Transform*)getComponent("Transform");
  particle.setPosition(Vector2(transform->getX(), transform->getY()));
}

Particle* Point::getParticleAddress() {
  return &particle;
}
*/


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
  //std::cout << (displayManager == NULL)  << std::endl;
  currentTexture = Managers::displayManager->makeTexture(imgPath);
  //std::cout << currentTexture  << std::endl;
  this->renderW = renderW;
  this->renderH = renderH;
}

Renderer::~Renderer() {
  if (currentTexture != NULL) {
    SDL_DestroyTexture(currentTexture);
  }
}

void Renderer::draw() {
  //if (DisplayManager::isFirstRender()) {
  //  DisplayManager::setFirstRender(false);
  //  DisplayManager::clearScreen();
  //}
  //DisplayManager::drawRect(transform->getX(), transform->getY(), 100, 100, DisplayManager::RED);
  //displayManager->drawTexture(transform->getX(), transform->getY(), renderW, renderH, currentTexture);
  SDL_Rect dest;
  dest.x = transform->getX();
  dest.y = transform->getY();
  //dest.x = 0;
  //dest.y = 0;
  dest.w = renderW;
  dest.h = renderH;
  //std::cout << (currentTexture == NULL) << std::endl;
  //std::cout << (displayManager->getRenderer() == NULL) << std::endl;
  SDL_RenderCopy(Managers::displayManager->getRenderer(), currentTexture, NULL, &dest);
}


void Renderer::update() {
  //Clears screen if this is the first obj to render
  /*
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
  */
}

void Renderer::start() {
  transform = (Transform*)getComponent("Transform");
}
