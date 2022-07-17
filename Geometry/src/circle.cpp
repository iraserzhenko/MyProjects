#include <iostream>
#include <cmath>
#include "../circle.h"
#include "../segment.h"
#include "../line.h"
geometry::Circle::Circle(int x_now, int y_now, int r_now) {
  center.x = x_now;
  center.y = y_now;
  r = r_now;
}
geometry::Circle::Circle(const Point& point, int radius) {
  center.x = point.x;
  center.y = point.y;

  r = radius;
}
geometry::IShape& geometry::Circle::Move(const Vector& vec) {
  center.x += vec.x;
  center.y += vec.y;
  return *this;
}
bool geometry::Circle::ContainsPoint(const Point& point) const {
  int contain = ((point.x - center.x) * (point.x - center.x) + (point.y - center.y) * (point.y - center.y));
  return (contain <= r * r);
}
bool geometry::Circle::CrossesSegment(const Segment& segment) const {
  int value1 = (segment.one.x - center.x) * (segment.one.x - center.x) +
               (segment.one.y - center.y) * (segment.one.y - center.y) - r * r;
  int value2 = (segment.two.x - center.x) * (segment.two.x - center.x) +
               (segment.two.y - center.y) * (segment.two.y - center.y) - r * r;
  if (value1 * value2 <= 0) {
    return true;
  }
  int dx = segment.two.x - segment.one.x;
  int dy = segment.two.y - segment.one.y;
  int x1 = segment.one.x;
  int y1 = segment.one.y;
  int x0 = center.x;
  int y0 = center.y;
  double a = dx * dx + dy * dy;
  double b = 2 * (dx * (x1 - center.x) + dy * (segment.one.y - center.y));
  double c = x0 * x0 + y0 * y0 + x1 * x1 + y1 * y1 - 2 * center.x * x1 - 2 * center.y * y1 - r * r;
  if (b * b < 4 * a * c) {
    return false;
  }
  double t1 = sqrt(b * b - 4 * a * c) - b;
  if (t1 > 2 * a || t1 < (-2) * a) {
    return false;
  }
  double t2 = (-1) * (sqrt(b * b - 4 * a * c) + b);
  return !(t2 > 2 * a || t2 < (-2) * a);
}
geometry::IShape* geometry::Circle::Clone() const {
  return new Circle(center, r);
}
std::string geometry::Circle::ToString() {
  std::string output = "Circle(Point(";
  std::string into_int = std::to_string(center.x);
  output += into_int;
  output += ", ";
  into_int = std::to_string(center.y);
  output += into_int;
  output += "), ";
  into_int = std::to_string(r);
  output += into_int;
  output += ")";
  return output;
}