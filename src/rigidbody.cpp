#include "../include/rigidbody.hpp"
#include "../include/managers.hpp"
#include "../include/timemanager.hpp"
#include <cmath>

double RigidBody::maxRotation = M_PI;

void RigidBody::integrate(double duration) {
  if (inverseMass <= 0) {
    return;
  }
  position.addScaledVector(velocity, duration);
  orientation += angularVelocity * duration;

  while (orientation >= RigidBody::maxRotation) {
    orientation -= RigidBody::maxRotation;
  }

  Vector2 resultingAcc = acceleration;
  resultingAcc.addScaledVector(forceAccum, inverseMass);

  velocity.addScaledVector(resultingAcc, duration);
  angularVelocity += (torqueAccum * inverseInertia * duration);

  //velocity *= pow(damping, duration);

  clearAccumulators();

}

void RigidBody::clearAccumulators() {
  forceAccum.clear();
  torqueAccum = 0;
}


void RigidBody::setPosition(Vector2 pos) {
  position = pos;
}
void RigidBody::setVelocity(Vector2 vel) {
  velocity = vel;
}
void RigidBody::setAcceleration(Vector2 acc) {
  acceleration = acc;
}
void RigidBody::setMass(double mass) {
  if (mass <= 0) {
    return;
  }
  inverseMass = 1 / mass;
}
void RigidBody::setInverseMass(double invMass) {
  inverseMass = invMass;
}


void RigidBody::addForce(const Vector2& force) {
  forceAccum += force;
  isAwake = true;
}

Vector2 RigidBody::getPosition() {
  return position;
}
Vector2* RigidBody::getPositionAddress() {
  return &position;
}
Vector2 RigidBody::getVelocity() {
  return velocity;
}
Vector2 RigidBody::getAcceleration() {
  return acceleration;
}
double RigidBody::getMass() {
  if (inverseMass <= 0) {
    return 0;
  }
  return (1 / inverseMass);
}
double RigidBody::getInverseMass() {
  return inverseMass;
}

double RigidBody::getOrientation() {
  return orientation;
}

RigidBody::RigidBody() {
  tag = "RigidBody";
  setMass(1);
}

RigidBody::RigidBody(double dx, double dy, double ddx, double ddy, double mass, double angle) {
  tag = "RigidBody";
  velocity = Vector2(dx, dy);
  acceleration = Vector2(ddx, ddy);
  orientation = angle;
  setMass(mass);
}



void RigidBody::update() {

  integrate(Managers::timeManager->getLastFrameDuration() / 1000.f);

}


void RigidBody::start() {
  transform = (Transform*)getComponent("Transform");
}
