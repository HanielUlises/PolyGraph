#pragma once

#include "Point.hpp"
#include "Polygon.hpp"

#include <memory>

namespace GeomCore {
    // Directions
    const int LEFT = 1;        // Point c is to the left of line segment ab
    const int RIGHT = -1;      // Point c is to the right of line segment ab
    const int BEHIND = 2;      // Point c is behind point a
    const int BEYOND = 3;      // Point c is beyond point b
    const int ORIGIN = 0;      // Point c coincides with point a
    const int DESTINATION = 4; // Point c coincides with point b
    const int BETWEEN = 5;     // Point c lies on line segment ab between a and b

    double area_triangle_2d(const PointR2 &a, const PointR2 &b, const PointR2 &c);
    static int orientation_R2(const PointR2& a, const PointR2& b, const PointR2& c);

    static bool left(const PointR2& a, const PointR2& b, const PointR2& c);
    static bool left_or_beyond(const PointR2& a, const PointR2& b, const PointR2& c);

    bool collinear(const Vector3d& a, const Vector3d& b);
    bool collinear(const PointR3& a, const PointR3& b, const PointR3& c);

    bool coplaner(const Vector3d& a, const Vector3d& b, const Vector3d& c);
    bool coplaner(const PointR3& a, const PointR3& b, const PointR3& c, const PointR3& d);

    bool is_diagonal(const std::shared_ptr<VertexR2> v1, const std::shared_ptr<VertexR2> v2, std::shared_ptr<PolygonR2> poly = nullptr);
}