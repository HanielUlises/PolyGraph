#pragma once

#include "Point.h"
#include "Polygon.h"

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
    int orientation_2d(const PointR2 &a, const PointR2 &b, const PointR2 &c);

    bool collinear(const Vector3f& a, const Vector3f& b);
    bool collinear(const PointR3& a, const PointR3& b, const PointR3& c);

    bool coplaner(const Vector3f& a, const Vector3f& b, const Vector3f& c);
    bool coplaner(const PointR3& a, const PointR3& b, const PointR3& c, const PointR3& d);

    bool is_diagonal(const std::shared_ptr<VertexR2> v1, const std::shared_ptr<VertexR2> v2, std::shared_ptr<PolygonR2> poly = nullptr);
}