#include "Point.h"
#include "Line.h"
#include "Plane.h"

namespace GeomCore{
    template<typename coord_type>
    coord_type distance(Line3d& line, PointR3& c);
    
    template<typename coord_type>
    coord_type distance(Plane_f& p, PointR3& c);
}