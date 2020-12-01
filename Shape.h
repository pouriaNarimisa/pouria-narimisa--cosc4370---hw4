#ifndef SHAPE_H
#define SHAPE_H

#include <Eigen/Dense>

namespace Raytracer148 {
struct Ray {
  Eigen::Vector3d origin, direction;
};

class Shape;

struct HitRecord {
  Eigen::Vector3d position, normal,color;
  double t;
  int shapeId;
};

class Shape {
public:
  virtual ~Shape(){}
  virtual HitRecord intersect(const Ray &ray) = 0;
  virtual Eigen::Vector3d getColor(const Eigen::Vector3d &position)=0;
  virtual double getReflectStrength() = 0;
};

}

#endif
