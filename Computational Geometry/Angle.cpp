#include "Angle.h"

template<class T, size_t dim>
static float get_angle(const GeomCore::Vector<T, dim>& v1,
                       const GeomCore::Vector<T, dim>& v2)
{
    // Magnitude of each vector
    const double mag1 = v1.magnitude();
    const double mag2 = v2.magnitude();

    // Degenerate case: zero-length vector(s)
    if (mag1 < TOLERANCE || mag2 < TOLERANCE) {
        return 0.0f;
    }

    // cosθ = |v1·v2| / (||v1|| ||v2||)   → guarantees θ ∈ [0, 90°]
    // To get the full [0, 180°] range we keep the absolute value
    const double cos_theta = std::fabs(dot_product(v1, v2)) / (mag1 * mag2);

    const double clamped = std::max(-1.0, std::min(1.0, cos_theta));

    const double theta_rad = std::acos(clamped);
    return static_cast<float>(radians_to_degrees(theta_rad));
}

float GeomCore::angle_lines_2D(const Line2d& l1, const Line2d& l2)
{
    return get_angle(l1.get_direction(), l2.get_direction());
}

float GeomCore::angle_lines_3D(const Line3d& l1, const Line3d& l2)
{
    return get_angle(l1.get_direction(), l2.get_direction());
}

float GeomCore::angle_planes(const Plane_f& p1, const Plane_f& p2)
{
    return get_angle(p1.get_normal(), p2.get_normal());
}