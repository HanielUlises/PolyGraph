#pragma once

#include "Point.h"
#include "Line.h"

namespace GeomCore{
    bool intersection(const Point2d&, const Point2d&, const Point2d&,
                     const Point2d&); 

    bool intersection(const Point2d&, const Point2d&, const Point2d&,
                     const Point2d&, const Point2d&); 

    bool intersection(const Line2d&, const Line2d&, const Point2d&); 
}