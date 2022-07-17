#ifndef GEOMETRY__RAY_H_
#define GEOMETRY__RAY_H_
#include "shape.h"
#include "point.h"
namespace geometry {
class Ray : public IShape {
 public:
  int x1;
  int y1;
  Vector v;
  Ray(int x_1, int y_1, int x_2, int y_2);
  Ray(const Point& one, const Point& two);
  IShape& Move(const Vector& vec) override;
  bool ContainsPoint(const Point& point) const override;
  bool CrossesSegment(const Segment& segment) const override;
  IShape* Clone() const override;
  std::string ToString() override;
};
}  // namespace geometry
#endif
