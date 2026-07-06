#include "Point.h"
#include "Line.h"
#include "Plane.h"

namespace GeomCore{
    template<typename coord_type>
    coord_type distance(Line3d& line, Point3d& c);
    
    template<typename coord_type>
    coord_type distance(Plane_f& p, Point3d& c);
}