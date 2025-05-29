#pragma once

#include "Point.h"

namespace jmk{
    double area_triangle_2d(const Point2d &a, const Point2d &b, const Point2d &c);

    int orientation_2d();
}