#ifndef GEOMETRY__VECTOR_H_
#define GEOMETRY__VECTOR_H_
namespace geometry {
class Point;
class Vector {
 public:
  int x;
  int y;
  Vector operator+() const;
  Vector operator-() const;
  Vector operator*(const int& scalar);
  Vector operator/(const int& scalar);
  Vector operator-=(const Vector& vec);
  Vector operator+=(const Vector& vec);
  Vector operator*=(const int& scalar);
  Vector operator/=(const int& scalar);
};
Vector operator+(const Vector& first, const Vector& sec);
Vector operator-(const Vector& first, const Vector& sec);
bool operator==(const Vector& first, const Vector& sec);
bool operator!=(const Vector& first, const Vector& sec);
}  // namespace geometry
geometry::Vector operator-(const geometry::Point& one, const geometry::Point& two);
#endif