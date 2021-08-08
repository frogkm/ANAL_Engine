#ifndef PHYSICSMANAGER_HPP
#define PHYSICSMANAGER_HPP

#include "../include/force.hpp"

//class Particle;

class PhysicsManager {
public:
  void updateForces(double duration);
  void addParticle(Particle* particle, ParticleForceGenerator* forceGenerator);
  void removeParticle(Particle* particle, ParticleForceGenerator* forceGenerator);

private:
  ParticleForceRegistry particleRegistry;
};
#endif
