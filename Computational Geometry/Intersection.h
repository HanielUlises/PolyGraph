#pragma once

#include "Point.h"
#include "Line.h"
#include "Plane.h"

namespace GeomCore{
    bool intersection(const PointR2&, const PointR2&, const PointR2&,
                     const PointR2&); 

    bool intersection(const PointR2&, const PointR2&, const PointR2&,
                     const PointR2&, const PointR2&); 

    bool intersection(const Line2d&, const Line2d&, const PointR2&); 
    bool intersection(const Line3d&, const Plane_f&, PointR3);
    bool intersection(const Plane_f&, const Plane_f&, Line3d&);
}