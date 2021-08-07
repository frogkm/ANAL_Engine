#ifndef VECTOR2_HPP
#define VECTOR2_HPP

class Vector2 {
  public:
    Vector2();
    Vector2(double x, double y);
    void set(double x, double y);
    void invert();
    void clear();
    void addScaledVector(const Vector2& vector, double scale);
    void normalize();
    double getX() const;
    double getY() const;
    Vector2 operator+(const Vector2 other);
    void operator+=(const Vector2 other);
    Vector2 operator-(const Vector2 other);
    void operator-=(const Vector2 other);
    Vector2 operator*(const double other);
    Vector2 operator/(const double other);
    void operator*=(const double other);
    double length();
  private:
    double x;
    double y;
};
#endif
