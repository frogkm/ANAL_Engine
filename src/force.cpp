#include "../include/force.hpp"
#include "../include/particle.hpp"
#include <iterator>
#include <cmath>

void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator* forceGenerator) {
  ParticleForceRegistration temp;
  temp.particle = particle;
  temp.forceGenerator = forceGenerator;
  registrations.push_back(temp);
}
void ParticleForceRegistry::remove(Particle* particle, ParticleForceGenerator* forceGenerator) {
  for (Registry::iterator i = registrations.begin(); i != registrations.end(); i++) {
    if ((*i).particle == particle && (*i).forceGenerator == forceGenerator) {
      registrations.erase(i);
      break;
    }
  }
}
void ParticleForceRegistry::clear() {
  registrations.clear();
}
void ParticleForceRegistry::updateForces(double duration) {
  Registry::iterator i = registrations.begin();
  for (; i != registrations.end(); i++) {
    i->forceGenerator->updateForce(i->particle, duration);
  }
}

ConstantForceGenerator::ConstantForceGenerator(const Vector2& constForce) {
  this->constForce = constForce;
}
void ConstantForceGenerator::updateForce(Particle *particle, double duration) {
  if (particle->getInverseMass() <= 0) {
    return;
  }
  particle->addForce(constForce * particle->getMass());
}

DragGenerator::DragGenerator(double k1, double k2) {
  this->k1 = k1;
  this->k2 = k2;
}

void DragGenerator::updateForce(Particle *particle, double duration) {
  Vector2 force = particle->getVelocity();
  double dragCoeff = force.length();
  dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;  //Simplified drag equation
  force.normalize();  //Get direction of current movement
  force *= -dragCoeff;  //Apply drag opposite direction to current (to slow us down)
  particle->addForce(force);
}

SpringGenerator::SpringGenerator(Particle* other, double springConstant, double restLength) {
  anchor = other->getPositionAddress(); //Grabs a pointer to the particle's position so it can keep up with updates
  this->springConstant = springConstant;
  this->restLength = restLength;
}

SpringGenerator::SpringGenerator(Vector2* anchor, double springConstant, double restLength) {
  this->anchor = anchor;
  this->springConstant = springConstant;
  this->restLength = restLength;
}
void SpringGenerator::updateForce(Particle *particle, double duration) {  //This will only apply spring force to one object.  For both to work you must create 2 seperate generators.
  Vector2 force = particle->getPosition();
  force -= (*anchor);
  double mag = force.length();
  //mag = abs(mag - restLength);
  mag = mag - restLength;
  mag *= springConstant;
  force.normalize();
  force *= -mag;
  //force *= -mag;
  particle->addForce(force);

}
