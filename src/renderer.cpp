#include "../include/renderer.hpp"
#include "../include/managers.hpp"
#include "../include/displaymanager.hpp"
#include "../include/rigidbody.hpp"
#include <string>



RectRenderer::RectRenderer(SDL_Color color, double renderW, double renderH) {
  tag = "RectRenderer";
  this->color = color;
  this->renderW = renderW;
  this->renderH = renderH;
}
void RectRenderer::update() {}

void RectRenderer::start() {
  transform = (Transform*)getComponent("Transform");
}
void RectRenderer::draw() {
  SDL_Rect dest;
  dest.x = transform->getX();
  dest.y = transform->getY();
  dest.w = renderW;
  dest.h = renderH;
  SDL_SetRenderDrawColor(Managers::displayManager->getRenderer(), color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(Managers::displayManager->getRenderer(), &dest);
}

Renderer::Renderer(std::string imgPath, double renderW, double renderH) {
  tag = "Renderer";
  currentTexture = Managers::displayManager->makeTexture(imgPath);
  this->renderW = renderW;
  this->renderH = renderH;
}

Renderer::~Renderer() {
  if (currentTexture != NULL) {
    SDL_DestroyTexture(currentTexture);
  }
}

void Renderer::draw() {
  SDL_Rect dest;
  dest.x = transform->getX();
  dest.y = transform->getY();
  dest.w = renderW;
  dest.h = renderH;
  SDL_RenderCopy(Managers::displayManager->getRenderer(), currentTexture, NULL, &dest);
}


void Renderer::update() {}

void Renderer::start() {
  transform = (Transform*)getComponent("Transform");
}


SpriteRenderer::SpriteRenderer(std::string imgPath, double renderW, double renderH) {
  tag = "SpriteRenderer";
  currentTexture = Managers::displayManager->makeTexture(imgPath);
  this->renderW = renderW;
  this->renderH = renderH;
}

SpriteRenderer::~SpriteRenderer() {
  if (currentTexture != NULL) {
    SDL_DestroyTexture(currentTexture);
  }
}

void SpriteRenderer::draw() {
  SDL_Rect dest;
  dest.x = transform->getX();
  dest.y = transform->getY();
  dest.w = renderW;
  dest.h = renderH;
  //SDL_RenderCopy(Managers::displayManager->getRenderer(), currentTexture, NULL, &dest);
  SDL_RenderCopyEx(Managers::displayManager->getRenderer(), currentTexture, NULL, &dest, rigidBody->getOrientation(), NULL, SDL_FLIP_NONE);
}


void SpriteRenderer::update() {}

void SpriteRenderer::start() {
  transform = (Transform*)getComponent("Transform");
  rigidBody = (RigidBody*)getComponent("RigidBody");
}
