#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP

#include "vector2.hpp"

class RigidBody {
protected:
  double inverseMass;
  double linearDamping;
  Vector2 position;
  double orientation;
  Vector2 velocity;
  Vector2 acceleration;
  double angularVelocity;
  double inverseInertia;
  Vector2 forceAccum;
  bool isAwake;
  double torqueAccum;

public:
  void setInertia(double inertia);
  void setInverseInertia(double inverseInertia);
  void setPosition(Vector2 pos);
  void setVelocity(Vector2 vel);
  void setAcceleration(Vector2 acc);
  void setMass(double mass);
  void setInverseMass(double invMass);
  //void setDamping(double damp);

  Vector2 getPosition();
  Vector2 getVelocity();
  Vector2 getAcceleration();
  double getMass();
  double getInverseMass();
  double getInertia();
  double getInverseInertia();

  void addForce(const Vector2& force);
  void clearAccumulators();
  Vector2* getPositionAddress();
  void addForceAtPoint(const Vector2 &force, const Vector2 &point);
  void integrate(double duration);

  static double maxRotation;




};
#endif
