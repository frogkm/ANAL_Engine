#include "../include/particle.hpp"
#include "../include/managers.hpp"
#include "../include/timemanager.hpp"
#include <cmath>

void Particle::integrate(double duration) {
  if (inverseMass <= 0) {
    return;
  }
  transform->getPosition().addScaledVector(velocity, duration);
  Vector2 resultingAcc = acceleration;

  resultingAcc.addScaledVector(forceAccum, inverseMass);


  velocity.addScaledVector(resultingAcc, duration);

  //velocity *= pow(damping, duration);

  clearAccumulator();

}

Particle::Particle() {
  tag = "Particle";
  setMass(1); //Can't leave mass at 0 by default...
}
Particle::Particle(double dx, double dy, double ddx, double ddy, double mass) {
  tag = "Particle";
  velocity = Vector2(dx, dy);
  acceleration = Vector2(ddx, ddy);
  setMass(mass);
}
void Particle::update() {

  //transform->set(particle.getPosition().getX(), particle.getPosition().getY());
  integrate(Managers::timeManager->getLastFrameDuration() / 1000.f);  //integrate using previous frame as an estimate

}
void Particle::start() {
  transform = (Transform*)getComponent("Transform");
  //position = Vector2(transform->getX(), transform->getY());
}



void Particle::setVelocity(Vector2 vel) {
  velocity = vel;
}
void Particle::setAcceleration(Vector2 acc) {
  acceleration = acc;
}
void Particle::setMass(double mass) {
  if (mass <= 0) {
    return;
  }
  inverseMass = 1 / mass;
}
void Particle::setInverseMass(double invMass) {
  inverseMass = invMass;
}
//void Particle::setDamping(double damp) {
//  damping = damp;
//}

void Particle::clearAccumulator() {
  forceAccum.clear();
}

void Particle::addForce(const Vector2& force) {
  forceAccum += force;
}


Vector2 Particle::getVelocity() {
  return velocity;
}

Vector2 Particle::getPosition(){  //NOT returning a reference unlike transform->getPosition()
  return transform->getPosition();
}
Vector2* Particle::getPositionAddress() {
  return &(transform->getPosition());
}

Vector2 Particle::getAcceleration() {
  return acceleration;
}
double Particle::getMass() {
  if (inverseMass <= 0) {
    return 0;
  }
  return (1 / inverseMass);
}
double Particle::getInverseMass() {
  return inverseMass;
}
//double Particle::getDamping() {
//  return damping;
//}
