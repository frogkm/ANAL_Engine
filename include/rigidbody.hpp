#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP

#include "vector2.hpp"
#include "component.hpp"

class Transform;

class RigidBody : public Component {
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
  Transform* transform;

public:
  RigidBody();
  RigidBody(double dx, double dy, double ddx, double ddy, double mass, double angle);
  void setInertia(double inertia);
  void setInverseInertia(double inverseInertia);
  void setPosition(Vector2 pos);
  void setVelocity(Vector2 vel);
  void setAcceleration(Vector2 acc);
  void setMass(double mass);
  void setInverseMass(double invMass);

  Vector2 getPosition();
  Vector2 getVelocity();
  Vector2 getAcceleration();
  double getMass();
  double getInverseMass();
  double getInertia();
  double getInverseInertia();
  double getOrientation();

  void addForce(const Vector2& force);
  void clearAccumulators();
  Vector2* getPositionAddress();
  void addForceAtPoint(const Vector2 &force, const Vector2 &point);
  void integrate(double duration);

  void update();
  void start();

  static double maxRotation;

};
#endif
