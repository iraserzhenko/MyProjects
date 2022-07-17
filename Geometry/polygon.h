#ifndef GEOMETRY__POLYGON_H_
#define GEOMETRY__POLYGON_H_
#include "shape.h"
#include "point.h"
#include <vector>
namespace geometry {
class Polygon : public IShape {
 public:
  std::vector<Point> polygon;
  explicit Polygon(std::vector<Point> points);
  bool ContainsPoint(const Point& point) const override;
  bool CrossesSegment(const Segment& segment) const override;
  IShape& Move(const Vector& vec) override;
  IShape* Clone() const override;
  std::string ToString() override;
};
}  // namespace geometry
#endif