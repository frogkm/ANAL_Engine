#include "../include/physicsmanager.hpp"


void PhysicsManager::updateForces(double duration) {
  particleRegistry.updateForces(duration);
}

void PhysicsManager::addParticle(Particle* particle, ParticleForceGenerator* forceGenerator) {
  particleRegistry.add(particle, forceGenerator);
}
void PhysicsManager::removeParticle(Particle* particle, ParticleForceGenerator* forceGenerator) {
  particleRegistry.remove(particle, forceGenerator);
}
