#include "Distance.h"

template<typename coord_type>
coord_type GeomCore::distance (Line3d &line, Point3d& c){
    auto AC = c - line.get_point();
    auto t = dot_product(line.get_direction(), AC);

    auto xt = line.get_point() + line.get_direction() * t;
    auto distance_vector = xt - c;
    return distance_vector.magnitude();
}

template<typename coord_type>
coord_type GeomCore::distance(Plane_f& p, Point3d& c){
    auto result = dot_product(p.get_normal(), c) - p.get_d();
    return result;
}