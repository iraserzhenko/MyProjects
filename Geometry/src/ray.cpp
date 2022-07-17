#include <iostream>
#include "../ray.h"
#include "../line.h"
#include "../segment.h"

geometry::Ray::Ray(int x_1, int y_1, int x_2, int y_2) {
  x1 = x_1;
  y1 = y_1;
  v = {x_2 - x_1, y_2 - y_1};
}
geometry::Ray::Ray(const Point& one, const Point& two) {
  x1 = one.x;
  y1 = one.y;
  v.x = two.x - one.x;
  v.y = two.y - one.y;
}
geometry::IShape& geometry::Ray::Move(const Vector& vec) {
  x1 += vec.x;
  y1 += vec.y;
  return *this;
}
bool geometry::Ray::ContainsPoint(const Point& point) const {
  long long int vector_sum = v.x * (point.y - y1) - v.y * (point.x - x1);
  long long int scalar_sum = v.x * (point.x - x1) + v.y * (point.y - y1);
  return ((vector_sum == 0) && (scalar_sum >= 0));
}
bool geometry::Ray::CrossesSegment(const Segment& segment) const {
  Segment seg = segment;
  Line line_of_ray(x1, y1, x1 + v.x, y1 + v.y);
  bool line_cross = line_of_ray.CrossesSegment(seg);
  long long int v1 = (x1 - seg.one.x) * (seg.two.y - seg.one.y) - (y1 - seg.one.y) * (seg.two.x - seg.one.x);
  long long int vector2 = v.x * (seg.two.y - seg.one.y) - v.y * (seg.two.x - seg.one.x);
  return ((line_cross == 1) && (v1 * vector2 <= 0));
}
geometry::IShape* geometry::Ray::Clone() const {
  return new Ray(x1, y1, x1 + v.x, y1 + v.y);
}
std::string geometry::Ray::ToString() {
  std::string output = "Ray(Point(";
  std::string into_int = std::to_string(x1);
  output += into_int;
  output += ", ";
  into_int = std::to_string(y1);
  output += into_int;
  output += "), Vector(";
  into_int = std::to_string(v.x);
  output += into_int;
  output += ", ";
  into_int = std::to_string(v.y);
  output += into_int;
  output += "))";
  return output;
}