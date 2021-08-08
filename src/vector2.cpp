#include <cmath>
#include "../include/vector2.hpp"

Vector2::Vector2(){
  this->set(0, 0);  //Default constructor
}

Vector2::Vector2(double x, double y){
  this->set(x, y);
}

void Vector2::set(double x, double y) {
  this->x = x;
  this->y = y;
}

void Vector2::invert() {
  x = -x;
  y = -y;
}

double Vector2::length() {  //rename magnitude
  return sqrt(((this->x) * (this->x)) + ((this->y) * (this->y)));
}

void Vector2::addScaledVector(const Vector2& vector, double scale) {
  x += vector.getX() * scale;
  y += vector.getY() * scale;
}

double Vector2::getX() const {
  return x;
}
double Vector2::getY() const {
  return y;
}

Vector2 Vector2::operator+(const Vector2 other){
  Vector2 temp;
  temp.set(x + other.x, y + other.y);
  return temp;
}

Vector2 Vector2::operator-(const Vector2 other){
  Vector2 temp;
  temp.set(x - other.x, y - other.y);
  return temp;
}

Vector2 Vector2::operator*(const double other){
  Vector2 temp;
  temp.set(x * other, y * other);
  return temp;
}

void Vector2::operator*=(const double other){
  x *= other;
  y *= other;
}

void Vector2::operator+=(const Vector2 other){
  x += other.getX();
  y += other.getY();
}

void Vector2::operator-=(const Vector2 other) {
  x -= other.getX();
  y -= other.getY();
}

Vector2 Vector2::operator/(const double other){
  Vector2 temp;
  temp.set(x / other, y / other);
  return temp;
}

void Vector2::clear() {
  x = 0;
  y = 0;
}

void Vector2::normalize() {
  double mag = length();
  x /= mag;
  y /= mag;
}
