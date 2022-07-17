#ifndef GEOMETRY__POINT_H_
#define GEOMETRY__POINT_H_
#include "shape.h"
#include "vector.h"
namespace geometry {
class Point : public IShape {
 public:
  int x;
  int y;
  Point();
  Point(int x_now, int y_now);
  IShape& Move(const Vector& vec) override;
  bool ContainsPoint(const Point& point) const override;
  bool CrossesSegment(const Segment& segment) const override;
  IShape* Clone() const override;
  std::string ToString() override;
};
}  // namespace geometry
#endif
