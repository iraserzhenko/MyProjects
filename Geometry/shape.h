#ifndef GEOMETRY__SHAPE_H_
#define GEOMETRY__SHAPE_H_
#include <string>
namespace geometry {
class Point;
class Vector;
class Segment;
class IShape {
 public:
  virtual IShape& Move(const Vector& vec) = 0;
  virtual bool ContainsPoint(const Point& point) const = 0;
  virtual bool CrossesSegment(const Segment& segment) const = 0;
  virtual IShape* Clone() const = 0;
  virtual std::string ToString() = 0;
  virtual ~IShape() = default;
};
}  // namespace geometry
#endif