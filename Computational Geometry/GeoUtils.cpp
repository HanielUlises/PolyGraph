#include "GeoUtils.h"

double GeomCore::area_triangle_2d(const Point2d &a, const Point2d &b, const Point2d &c){
    auto AB = b - a;
    auto AC = c - a;

    auto result = cross_product_R2(AB, AC);
    return result / 2;
}

int GeomCore::orientation_2d(const Point2d &a, const Point2d &b, const Point2d &c){
    auto area = area_triangle_2d(a, b, c);
    
    if(area > 0 && area < TOLERANCE)
        area = 0;
    else if(area > 0 && area > TOLERANCE)
        area = 0;


    Vector2f ab = b - a;
    Vector2f ac = a - c;
    
    if(area > 0)
        return LEFT;
    else if(area < 0)
        return RIGHT;
    else if ((ab[X] * ac[X] < 0) || (ab[Y] * ac[Y] < 0))
        return BEHIND; 

    if(ab.magnitude() < ac.magnitude())
        return BEYOND;
    else if (a == c)
        return ORIGIN;
    else if (b == c)
        return DESTINATION;

    return BETWEEN;
}