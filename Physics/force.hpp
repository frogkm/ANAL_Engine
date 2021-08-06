#ifndef FORCE_HPP
#define FORCE_HPP
#include "vector2.hpp"
#include <vector>

class Particle;


class ParticleForceGenerator {
  public:
    virtual void updateForce(Particle *particle, double duration) = 0;

};

class ParticleForceRegistry {
protected:
  struct ParticleForceRegistration {
    Particle *particle;
    ParticleForceGenerator *forceGenerator;
  };
  typedef std::vector<ParticleForceRegistration> Registry;
  Registry registrations;
public:
  void add(Particle* particle, ParticleForceGenerator* forceGenerator);
  void remove(Particle* particle, ParticleForceGenerator* forceGenerator);
  void clear();
  void updateForces(double duration);

};


class ConstantForceGenerator : public ParticleForceGenerator{  //Mostly only used for gravity
  public:
    ConstantForceGenerator(const Vector2& constForce);
    void updateForce(Particle *particle, double duration);
  private:
    Vector2 constForce;
};

class DragGenerator : public ParticleForceGenerator{
  public:
    DragGenerator(double k1, double k2);
    void updateForce(Particle *particle, double duration);
  private:
    double k1; //drag coefficents
    double k2;
};

#endif
