#ifndef GEOMETRY__LINE_H_
#define GEOMETRY__LINE_H_
#include "shape.h"
#include "point.h"
namespace geometry {
class Line : public IShape {
 public:
  int a;
  int b;
  int c;
  Line(int x_1, int y_1, int x_2, int y_2);
  Line(const Point& first_p, const Point& sec_p);
  Line(int a_now, int b_now, int c_now);
  IShape& Move(const Vector& vec) override;
  bool ContainsPoint(const Point& point) const override;
  bool CrossesSegment(const Segment& segment) const override;
  IShape* Clone() const override;
  std::string ToString() override;
};
}  // namespace geometry
#endif
