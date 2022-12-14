#include "CoordinateSystem.hpp"
#include "MGeomerty/Point.hpp"

mgm::Point2u CoordSystem::transform(const mgm::Point2f &point) const{
    return {
        static_cast<unsigned>((point.x + offset_.x) * scaleX_) + rect_.x,
        static_cast<unsigned>((point.y + offset_.y) * scaleY_) + rect_.y
    };
}

mgm::Point2f CoordSystem::rTransform(const mgm::Point2u &point) const{
    return {
        ((point.x - rect_.x) / scaleX_) - offset_.x,
        ((point.y - rect_.y) / scaleY_) - offset_.y
    };
}
