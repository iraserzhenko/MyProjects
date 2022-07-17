#ifndef GEOMETRY__SEGMENT_H_
#define GEOMETRY__SEGMENT_H_
#include "shape.h"
#include "point.h"
namespace geometry {
class Segment : public IShape {
 public:
  Point one;
  Point two;
  Segment(int x_1, int y_1, int x_2, int y_2);
  Segment(const Point& first, const Point& sec);
  IShape& Move(const Vector& vec) override;
  bool ContainsPoint(const Point& point) const override;
  bool CrossesSegment(const Segment& segment) const override;
  IShape* Clone() const override;
  std::string ToString() override;
};
}  // namespace geometry
#endif
