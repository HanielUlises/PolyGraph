#include "SphericalGeometry.hpp"
#include <cmath>
#include <algorithm>
#include <stdexcept>

namespace GeomCore {

    template<typename T>
    requires Real<T>
    static T sphere_radius(const Manifold<T>& manifold) {
        if (manifold.kind() != GeometryKind::Spherical) {
            throw std::invalid_argument("Manifold is not spherical");
        }
        return T{1} / std::sqrt(manifold.curvature.value);
    }

    template<typename T>
    requires Real<T>
    T spherical_distance(const Manifold<T>& manifold, const PointR3& p1, const PointR3& p2) {
        T radius = sphere_radius(manifold);

        T dot = static_cast<T>(dot_product(p1, p2));
        T mag1 = static_cast<T>(p1.magnitude());
        T mag2 = static_cast<T>(p2.magnitude());

        T cos_theta = dot / (mag1 * mag2);
        cos_theta = std::clamp(cos_theta, T{-1}, T{1});

        return radius * std::acos(cos_theta);
    }

    template<typename T>
    requires Real<T>
    T spherical_angle(const Manifold<T>& manifold, const PointR3& p1, const PointR3& p2, const PointR3& p3) {
        T radius = sphere_radius(manifold);

        T a = spherical_distance(manifold, p2, p3);
        T b = spherical_distance(manifold, p1, p2);
        T c = spherical_distance(manifold, p1, p3);

        T cos_angle = (std::cos(c / radius) - std::cos(a / radius) * std::cos(b / radius)) /
                      (std::sin(a / radius) * std::sin(b / radius));
        cos_angle = std::clamp(cos_angle, T{-1}, T{1});

        return std::acos(cos_angle);
    }

    template<typename T>
    requires Real<T>
    PointR3 spherical_geodesic_point(const Manifold<T>& manifold, const PointR3& p1, const PointR3& p2, T t) {
        T radius = sphere_radius(manifold);

        T dot = static_cast<T>(dot_product(p1, p2));
        T mag1 = static_cast<T>(p1.magnitude());
        T mag2 = static_cast<T>(p2.magnitude());

        T omega = std::acos(std::clamp(dot / (mag1 * mag2), T{-1}, T{1}));

        if (omega < static_cast<T>(TOLERANCE)) {
            return p1;
        }

        T sin_omega = std::sin(omega);
        T coeff1 = std::sin((T{1} - t) * omega) / sin_omega;
        T coeff2 = std::sin(t * omega) / sin_omega;

        Vector3d result = p1 * coeff1 + p2 * coeff2;
        result.normalize();

        return result * static_cast<double>(radius);
    }

    template<typename T>
    requires Real<T>
    bool is_on_sphere(const Manifold<T>& manifold, const PointR3& p, T tolerance) {
        T radius = sphere_radius(manifold);
        T mag = static_cast<T>(p.magnitude());
        return std::fabs(mag - radius) <= tolerance;
    }

    template double spherical_distance<double>(const Manifold<double>&, const PointR3&, const PointR3&);
    template double spherical_angle<double>(const Manifold<double>&, const PointR3&, const PointR3&, const PointR3&);
    template PointR3 spherical_geodesic_point<double>(const Manifold<double>&, const PointR3&, const PointR3&, double);
    template bool is_on_sphere<double>(const Manifold<double>&, const PointR3&, double);

}