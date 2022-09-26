#include "RenderSphere.hpp"


namespace RTObjs {

double RenderSphere::getIntersection(const mgm::Ray3f& ray, SurfacePoint* pt) const {
    mgm::Point3f intersect;

    if(sph_.contains(ray.start())) return NoIntersection;

    assert(!sph_.contains(ray.start()));

    if(!mgm::intersect1(ray, sph_, &intersect)){
        return NoIntersection;
    }

    if(pt == nullptr) return (intersect - ray.start()).len();

    pt->point = intersect;
    pt->normal = mgm::normalize(intersect - sph_.center());
    pt->color = color_;
    pt->reflCoef = 0.9;
    pt->refrCoef = 0.7;
    pt->isSource = isSource_;

    return (intersect - ray.start()).len();
}


mgm::Point3f RenderSphere::getCenter() const{
    return sph_.center();
}
aGL::Color   RenderSphere::getColor () const{
    return color_;
}

}