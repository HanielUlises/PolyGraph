#include "Distance.h"

float GeomCore::distance(Line3d &line, Point3d& c){
    auto AC = c - line.get_point();
    auto t = dot_product(line.get_direction(), AC);

    auto xt = line.get_point() + line.get_direction() * t;
    auto distance_vector = xt - c;
    return distance_vector.magnitude();
}