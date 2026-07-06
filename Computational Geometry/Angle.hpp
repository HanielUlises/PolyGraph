#include "Line.h"
#include "Plane.h"
#include "Core.h"

namespace GeomCore {
    float angle_lines_2D(const Line2d& l1, const Line2d& l2);
    float angle_lines_3D(const Line3d& l1, const Line3d& l2);
    float angle_line_plane(const Line3d& l1, const Plane_f& p);
    float angle_planes(const Plane_f& p1, const Plane_f& p2);
} // namespace Geomcore