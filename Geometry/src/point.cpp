#include <iostream>
#include "../point.h"
#include "../segment.h"
geometry::Point::Point() {
  x = 0;
  y = 0;
}
geometry::Point::Point(int x_now, int y_now) {
  x = x_now;
  y = y_now;
}
std::string geometry::Point::ToString() {
  std::string output = "Point(";
  std::string into_int = std::to_string(x);
  output += into_int;
  output += ", ";
  into_int = std::to_string(y);
  output += into_int;
  output += ")";
  return output;
}
geometry::IShape& geometry::Point::Move(const Vector& vec) {
  x += vec.x;
  y += vec.y;
  return *this;
}
bool geometry::Point::ContainsPoint(const Point& point) const {
  return ((x == point.x) && (y == point.y));
}
bool geometry::Point::CrossesSegment(const Segment& segment) const {
  int vector_p = (x - segment.one.x) * (segment.two.y - y) - (segment.two.x - x) * (y - segment.one.y);
  int scalar_p = (x - segment.one.x) * (segment.two.x - x) + (y - segment.one.y) * (segment.two.y - y);
  return ((vector_p == 0) && (scalar_p >= 0));
}
geometry::IShape* geometry::Point::Clone() const {
  return new Point(x, y);
}