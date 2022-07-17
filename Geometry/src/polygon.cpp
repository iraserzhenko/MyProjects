#include <iostream>
#include "../polygon.h"
#include "../segment.h"
#include "../ray.h"

geometry::Polygon::Polygon(std::vector<Point> points) {
  int n = points.size();
  for (int i = 0; i < n; i++) {
    polygon.push_back(points[i]);
  }
}
geometry::IShape& geometry::Polygon::Move(const Vector& vec) {
  int n = polygon.size();
  for (int i = 0; i < n; i++) {
    polygon[i].x += vec.x;
    polygon[i].y += vec.y;
  }
  return *this;
}
bool geometry::Polygon::ContainsPoint(const Point& point) const {
  int v_x = 1;
  int v_y = 0;
  int counter = 0;
  int a = v_y;
  int b = (-1) * v_x;
  int c = (point.x + v_x) * point.y - (point.y + v_y) * point.x;
  int n = polygon.size();
  Ray ray(point.x, point.y, point.x + v_x, point.y + v_y);
  for (int i = 0; i < (n - 1); i++) {
    int term1 = (a * polygon[i].x) + (b * polygon[i].y) + c;
    int term2 = (a * polygon[i + 1].x) + (b * polygon[i + 1].y) + c;
    Segment seg(polygon[i].x, polygon[i].y, polygon[i + 1].x, polygon[i + 1].y);
    if (term1 * term2 <= 0) {
      bool test = ray.CrossesSegment(seg);
      if (test == 1) {
        if (polygon[i].y == point.y && polygon[i + 1].y == point.y) {
        } else if (polygon[i].y == point.y || polygon[i + 1].y == point.y) {
          if (std::max(polygon[i].y, polygon[i + 1].y) == point.y) {
            counter++;
          }
        } else {
          counter++;
        }
      }
    }
    bool contain = seg.ContainsPoint(point);
    if (contain == 1) {
      return true;
    }
  }
  Segment last(polygon[n - 1].x, polygon[n - 1].y, polygon[0].x, polygon[0].y);
  int term1 = (a * polygon[n - 1].x) + (b * polygon[n - 1].y) + c;
  int term2 = (a * polygon[0].x) + (b * polygon[0].y) + c;
  if (term1 * term2 <= 0) {
    bool last_test = ray.CrossesSegment(last);
    if (last_test == 1) {
      if (polygon[n - 1].y == point.y && polygon[0].y == point.y) {
      } else if (polygon[0].y == point.y || polygon[n - 1].y == point.y) {
        if (std::max(polygon[0].y, polygon[n - 1].y) == point.y) {
          counter++;
        }
      } else {
        counter++;
      }
    }
  }
  bool last_contain = last.ContainsPoint(point);
  if (last_contain == 1) {
    return true;
  }
  return ((counter % 2) == 1);
}
bool geometry::Polygon::CrossesSegment(const Segment& segment) const {
  int n = polygon.size();
  for (int i = 0; i < (n - 1); i++) {
    Segment seg(polygon[i].x, polygon[i].y, polygon[i + 1].x, polygon[i + 1].y);
    bool test = seg.CrossesSegment(segment);
    if (test == 1) {
      return true;
    }
  }
  Segment last(polygon[n - 1].x, polygon[n - 1].y, polygon[0].x, polygon[0].y);
  bool last_test = last.CrossesSegment(segment);
  return (last_test == 1);
}
geometry::IShape* geometry::Polygon::Clone() const {
  return new Polygon(polygon);
}
std::string geometry::Polygon::ToString() {
  int n = polygon.size();
  std::string output = "Polygon(";
  std::string into_int;
  for (int i = 0; i < n; i++) {
    output += "Point(";
    into_int = std::to_string(polygon[i].x);
    output += into_int;
    output += ", ";
    into_int = std::to_string(polygon[i].y);
    output += into_int;
    if (i < (n - 1)) {
      output += "), ";
    } else {
      output += ")";
    }
  }
  output += ")";
  return output;
}