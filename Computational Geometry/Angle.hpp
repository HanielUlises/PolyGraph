#include "Line.hpp"
#include "Plane.hpp"
#include "Core.hpp"


namespace GeomCore {
    template<class T>
    T angle_lines_2D(const Line2d& l1, const Line2d& l2);

    template<class T>
    T angle_lines_3D(const Line3d& l1, const Line3d& l2);

    template<class T>
    T angle_line_plane(const Line3d& l1, const Plane_d& p);

    template<class T>
    T angle_planes(const Plane_d& p1, const Plane_d& p2);
} // namespace Geomcore