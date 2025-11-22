#pragma once

#include "Point.h"
#include "Line.h"
#include "Plane.h"

namespace GeomCore{
    bool intersection(const Point2d&, const Point2d&, const Point2d&,
                     const Point2d&); 

    bool intersection(const Point2d&, const Point2d&, const Point2d&,
                     const Point2d&, const Point2d&); 

    bool intersection(const Line2d&, const Line2d&, const Point2d&); 
    bool intersection(const Line3d&, const Plane_f&, Point3d&);
    bool intersection(const Plane_f&, const Plane_f&, Line3d&);
}