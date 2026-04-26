#pragma once

#include "Point.hpp"
#include "Line.hpp"
#include "Plane.hpp"

namespace GeomCore{
    bool intersection(const PointR2&, const PointR2&, const PointR2&,
                     const PointR2&); 

    bool intersection(const PointR2&, const PointR2&, const PointR2&,
                     const PointR2&, const PointR2&); 

    bool intersection(const Line2d&, const Line2d&, const PointR2&); 
    bool intersection(const Line3d&, const Plane_d&, PointR3);
    bool intersection(const Plane_d&, const Plane_d&, Line3d&);
}