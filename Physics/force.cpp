#include "force.hpp"
#include "particle.hpp"
#include <iterator>

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
  dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;
  force.normalize();
  force *= -dragCoeff;
  particle->addForce(force);
}
