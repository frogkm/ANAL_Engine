#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include "vector2.hpp"
#include "component.hpp"

class Transform;

class Particle : public Component {
  public:
    void integrate(double duration);
    void setVelocity(Vector2 vel);
    void setAcceleration(Vector2 acc);
    void setMass(double mass);
    void setInverseMass(double invMass);
    //void setDamping(double damp);

    Vector2 getVelocity();
    Vector2 getAcceleration();
    double getMass();
    double getInverseMass();
    Vector2 getPosition();
    //double getDamping();

    void clearAccumulator();
    void addForce(const Vector2& force);
    Vector2* getPositionAddress();

    Particle();
    Particle(double dx, double dy, double ddx, double ddy, double mass);
    void update();
    void start();


  protected:
    //Vector2 position;
    Vector2 velocity;
    Vector2 acceleration; //Only used for constant accelerations like gravity, etc. -- Never changes unlike most other forces
    double inverseMass;
    //double damping;

    Vector2 forceAccum;

    Transform* transform;
};
#endif
