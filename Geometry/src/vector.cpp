#include "../vector.h"
#include "../point.h"
namespace geometry {
Vector Vector::operator+() const {
  return *this;
}
Vector Vector::operator-() const {
  Vector copy = *this;
  copy.x *= (-1);
  copy.y *= (-1);
  return copy;
}
Vector Vector::operator*(const int &scalar) {
  x *= scalar;
  y *= scalar;
  return *this;
}
Vector Vector::operator/(const int &scalar) {
  x /= scalar;
  y /= scalar;
  return *this;
}
Vector Vector::operator-=(const Vector &vec) {
  x -= vec.x;
  y -= vec.y;
  return *this;
}
Vector Vector::operator+=(const Vector &vec) {
  x += vec.x;
  y += vec.y;
  return *this;
}
Vector Vector::operator*=(const int &scalar) {
  x *= scalar;
  y *= scalar;
  return *this;
}
Vector Vector::operator/=(const int &scalar) {
  x /= scalar;
  y /= scalar;
  return *this;
}
Vector operator+(const Vector &first, const Vector &sec) {
  Vector copy = first;
  copy.x += sec.x;
  copy.y += sec.y;
  return copy;
}
Vector operator-(const Vector &first, const Vector &sec) {
  Vector copy = first;
  copy.x -= sec.x;
  copy.y -= sec.y;
  return copy;
}
bool operator==(const Vector &first, const Vector &sec) {
  return ((first.x == sec.x) && (first.y == sec.y));
}
bool operator!=(const Vector &first, const Vector &sec) {
  return !((first.x == sec.x) && (first.y == sec.y));
}
}  // namespace geometry
geometry::Vector operator-(const geometry::Point &one, const geometry::Point &two) {
  return geometry::Vector{one.x - two.x, one.y - two.y};
}