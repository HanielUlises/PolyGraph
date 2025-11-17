#pragma once

#include "Point.h"

namespace GeomCore {
    // Directions
    const int LEFT = 1;        // Point c is to the left of line segment ab
    const int RIGHT = -1;      // Point c is to the right of line segment ab
    const int BEHIND = 2;      // Point c is behind point a
    const int BEYOND = 3;      // Point c is beyond point b
    const int ORIGIN = 0;      // Point c coincides with point a
    const int DESTINATION = 4; // Point c coincides with point b
    const int BETWEEN = 5;     // Point c lies on line segment ab between a and b

    double area_triangle_2d(const Point2d &a, const Point2d &b, const Point2d &c);
    int orientation_2d(const Point2d &a, const Point2d &b, const Point2d &c);

    bool collinear(const Vector3f& a, const Vector3f& b);
    bool collinear(const Point3d& a, const Point3d& b, const Point3d& c);

    bool coplaner(const Vector3f& a, const Vector3f& b, const Vector3f& c);
    bool coplaner(const Point3d& a, const Point3d& b, const Point3d& c, const Point3d& d);
}