#include <iostream>
#include "../line.h"
#include "../segment.h"

geometry::Line::Line(int x_1, int y_1, int x_2, int y_2) {
  a = (y_2 - y_1);
  b = (x_1 - x_2);
  c = x_2 * y_1 - x_1 * y_2;
}
geometry::Line::Line(const Point& first_p, const Point& sec_p) {
  a = sec_p.y - first_p.y;
  b = (-1) * (sec_p.x - first_p.x);
  c = (sec_p.x * first_p.y) - (first_p.x * sec_p.y);
}
geometry::Line::Line(int a_now, int b_now, int c_now) {
  a = a_now;
  b = b_now;
  c = c_now;
}
geometry::IShape& geometry::Line::Move(const Vector& vec) {
  c -= a * vec.x + b * vec.y;
  return *this;
}
bool geometry::Line::ContainsPoint(const Point& point) const {
  return (a * point.x + b * point.y + c == 0);
}
bool geometry::Line::CrossesSegment(const Segment& segment) const {
  int term1 = a * segment.one.x + b * segment.one.y;
  if (term1 < (-1) * c) {
    term1 = -1;
  } else if (term1 == (-1) * c) {
    term1 = 0;
  } else {
    term1 = 1;
  }
  int term2 = a * segment.two.x + b * segment.two.y;
  if (term2 < (-1) * c) {
    term2 = -1;
  } else if (term2 == (-1) * c) {
    term2 = 0;
  } else {
    term2 = 1;
  }
  return (term1 * term2 <= 0);
}
geometry::IShape* geometry::Line::Clone() const {
  return new Line(a, b, c);
}
std::string geometry::Line::ToString() {
  std::string output = "Line(";
  std::string into_int = std::to_string(a);
  output += into_int;
  output += ", ";
  into_int = std::to_string(b);
  output += into_int;
  output += ", ";
  into_int = std::to_string(c);
  output += into_int;
  output += ")";
  return output;
}