#include <iostream>
#include "../segment.h"
#include "../line.h"

geometry::Segment::Segment(int x_1, int y_1, int x_2, int y_2) {
  one.x = x_1;
  one.y = y_1;
  two.x = x_2;
  two.y = y_2;
}
geometry::Segment::Segment(const Point& first, const Point& sec) {
  one.x = first.x;
  one.y = first.y;
  two.x = sec.x;
  two.y = sec.y;
}
geometry::IShape& geometry::Segment::Move(const Vector& vec) {
  one.x += vec.x;
  two.x += vec.x;
  one.y += vec.y;
  two.y += vec.y;
  return *this;
}
bool geometry::Segment::ContainsPoint(const Point& point) const {
  int vector_sum = (one.x - point.x) * (point.y - two.y) - (one.y - point.y) * (point.x - two.x);
  int scalar_sum = (one.x - point.x) * (point.x - two.x) + (one.y - point.y) * (point.y - two.y);
  return ((vector_sum == 0) && (scalar_sum >= 0));
}
bool geometry::Segment::CrossesSegment(const Segment& segment) const {
  Line ab(one, two);
  Line cd(segment.one, segment.two);
  bool term_ab = ab.CrossesSegment(segment);
  bool term_cd = cd.CrossesSegment(*this);
  int max_x = std::max(std::max(segment.one.x, segment.two.x), std::max(one.x, two.x));
  int min_x = std::min(std::min(segment.one.x, segment.two.x), std::min(one.x, two.x));
  int max_y = std::max(std::max(segment.one.y, segment.two.y), std::max(one.y, two.y));
  int min_y = std::min(std::min(segment.one.y, segment.two.y), std::min(one.y, two.y));
  int s_x = abs(segment.one.x - segment.two.x);
  int s_y = abs(segment.one.y - segment.two.y);
  int t_x = abs(one.x - two.x);
  int t_y = abs(one.y - two.y);
  return ((term_ab == 1 && term_cd == 1) && (max_x - min_x <= s_x + t_x) && (max_y - min_y <= s_y + t_y));
}
geometry::IShape* geometry::Segment::Clone() const {
  return new Segment(one, two);
}
std::string geometry::Segment::ToString() {
  std::string output = "Segment(Point(";
  std::string into_int = std::to_string(one.x);
  output += into_int;
  output += ", ";
  into_int = std::to_string(one.y);
  output += into_int;
  output += "), Point(";
  into_int = std::to_string(two.x);
  output += into_int;
  output += ", ";
  into_int = std::to_string(two.y);
  output += into_int;
  output += "))";
  return output;
}