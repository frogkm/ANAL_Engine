#include "../include/particle.hpp"
#include <cmath>

void Particle::integrate(double duration) {
  if (inverseMass <= 0) {
    return;
  }
  position.addScaledVector(velocity, duration);
  Vector2 resultingAcc = acceleration;

  resultingAcc.addScaledVector(forceAccum, inverseMass);


  velocity.addScaledVector(resultingAcc, duration);

  //velocity *= pow(damping, duration);

  clearAccumulator();

}

void Particle::setPosition(Vector2 pos) {
  position = pos;
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

Vector2 Particle::getPosition() {
  return position;
}
Vector2* Particle::getPositionAddress() {
  return &position;
}
Vector2 Particle::getVelocity() {
  return velocity;
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
