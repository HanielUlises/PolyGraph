#include "Core.h"
#include "Intersection.h"
#include "GeoUtils.h"

bool GeomCore::intersection(const Point2d& a, const Point2d&b, const Point2d&c,
                            const Point2d& d){
    auto ab_c = orientation_2d(a, b, c);
    auto ab_d = orientation_2d(a, b, d);
    auto cd_a = orientation_2d(c, d, a);
    auto cd_b = orientation_2d(c, d, b);

    if(ab_c == BETWEEN || ab_c == ORIGIN || ab_c == DESTINATION
     ||ab_d == BETWEEN || ab_d == ORIGIN || ab_d == DESTINATION
     ||cd_a == BETWEEN || cd_a == ORIGIN || cd_a == DESTINATION
     ||cd_b == BETWEEN || cd_b == ORIGIN || cd_b == DESTINATION){
        return true;
    }

    return _xor(ab_c == LEFT, ab_d == LEFT) && _xor(cd_a == LEFT, cd_b == LEFT);
}

bool GeomCore::intersection(const Point2d& a, const Point2d&b, const Point2d&c,
                            const Point2d& d, Point2d& intersection){
    Vector2f AB = b - a;
    Vector2f CD = d - c;
    
    Vector2f n(CD[Y], -CD[X]);
    
    auto denominator = dot_product(n, AB);

    if(is_equal_1D(denominator, 0)){
        auto AC = c - a;
        auto numerator = dot_product(n, AC);

        auto t = numerator/denominator;

        auto x = a[X] + t * AB[X];
        auto y = a[Y] + t * AB[Y];

        intersection.assign(X, x);
        intersection.assign(Y, y);
        return true;
    }
    else return false;
}

bool GeomCore::intersection(const Line2d& l1, const Line2d& l2, const Point2d& _intersection){
    auto l1_start = l1.get_point();
    auto l1_end = l1_start + l1.get_direction();

    auto l2_start = l2.get_point();
    auto l2_end = l2_start + l2.get_direction();

    return intersection(l1_start, l1_end, l2_start, l2_end, _intersection);
}