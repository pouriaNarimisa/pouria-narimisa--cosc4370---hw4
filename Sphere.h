#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

namespace Raytracer148 {
class Sphere : public Shape {
public:
    Sphere(Eigen::Vector3d &center, Eigen::Vector3d &color,double radius, double reflectStrength) : c(center), r(radius) ,paintcolor(color),reflect(reflectStrength){}

    virtual HitRecord intersect(const Ray &ray);
    virtual Eigen::Vector3d getColor(const Eigen::Vector3d &position);
    virtual double getReflectStrength();

private:
    Eigen::Vector3d c;
    Eigen::Vector3d paintcolor;
    double r;
    double reflect;
};
}

#endif
