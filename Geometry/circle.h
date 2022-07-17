#ifndef GEOMETRY__CIRCLE_H_
#define GEOMETRY__CIRCLE_H_
#include "shape.h"
#include "point.h"
namespace geometry {
class Circle : public IShape {
 public:
  Point center;
  int r;
  Circle(int x_now, int y_now, int r_now);
  Circle(const Point& point, int radius);
  IShape& Move(const Vector& vec) override;
  bool ContainsPoint(const Point& point) const override;
  bool CrossesSegment(const Segment& segment) const override;
  IShape* Clone() const override;
  std::string ToString() override;
};
}  // namespace geometry
#endif
