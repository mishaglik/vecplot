#ifndef MGEOMERTY_INTERSECTS_HPP
#define MGEOMERTY_INTERSECTS_HPP

#include <MGeomerty/Point.hpp>
#include <MGeomerty/Line.hpp>
#include <MGeomerty/Sphere.hpp>

namespace mgm {
    double distBtw(const Line3f& line, const Point3f& pt);

    Vector3f getReflection(const Vector3f& v, const Vector3f& u);

    bool intersect1(const Sphere3f& sph, const Line3f& line, Point3f* pt = nullptr);
    bool intersect1(const Sphere3f& sph, const Ray3f&   ray, Point3f* pt = nullptr);

    bool intersect1(const Line3f& line, const Sphere3f& sph, Point3f* pt = nullptr);
    bool intersect1(const Ray3f&  ray,  const Sphere3f& sph, Point3f* pt = nullptr);

}

#endif /* MGEOMERTY_INTERSECTS_HPP */
