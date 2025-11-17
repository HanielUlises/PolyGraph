#include "Angle.h"

float GeomCore::angle_lines_2D(const Line2d& l1, const Line2d& l2){
    const auto& d1 = l1.get_direction();
    const auto& d2 = l2.get_direction();

    const double mag1 = d1.magnitude();
    const double mag2 = d2.magnitude();

    if (mag1 < TOLERANCE || mag2 < TOLERANCE) {
        return 0.0f;   
    }

    const double cos_theta = std::fabs(dot_product(d1, d2)) / (mag1 * mag2);
    const double clamped = std::fmin(1.0, std::fmax(0.0, cos_theta));

    const double theta_rad = std::acos(clamped);

    return static_cast<float>(radians_to_degrees(theta_rad));
}

float GeomCore::angle_lines_3D(const Line3d& l1, const Line3d& l2){
    const auto& d1 = l1.get_direction();
    const auto& d2 = l2.get_direction();

    const double mag1 = d1.magnitude();
    const double mag2 = d2.magnitude();

    if (mag1 < TOLERANCE || mag2 < TOLERANCE) {
        return 0.0f;
    }

    const double cos_theta = std::fabs(dot_product(d1, d2)) / (mag1 * mag2);
    const double clamped = std::fmin(1.0, std::fmax(0.0, cos_theta));

    const double theta_rad = std::acos(clamped);

    return static_cast<float>(radians_to_degrees(theta_rad));

}