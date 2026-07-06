#include "HyperbolicGeometry.hpp"
#include <cmath>
#include <algorithm>
#include <stdexcept>

namespace GeomCore {

    template<typename T>
    requires Real<T>
    static T hyperboloid_radius(const Manifold<T>& manifold) {
        if (manifold.kind() != GeometryKind::Hyperbolic) {
            throw std::invalid_argument("Manifold is not hyperbolic");
        }
        return T{1} / std::sqrt(-manifold.curvature.value);
    }

    template<typename T>
    requires Real<T>
    T minkowski_bilinear_form(const PointR3& p1, const PointR3& p2) {
        return static_cast<T>(p1[X] * p2[X] + p1[Y] * p2[Y] - p1[Z] * p2[Z]);
    }

    template<typename T>
    requires Real<T>
    bool is_on_hyperboloid(const Manifold<T>& manifold, const PointR3& p, T tolerance) {
        T radius = hyperboloid_radius(manifold);
        T form = minkowski_bilinear_form<T>(p, p);
        return std::fabs(form + radius * radius) <= tolerance;
    }

    template<typename T>
    requires Real<T>
    T hyperbolic_distance(const Manifold<T>& manifold, const PointR3& p1, const PointR3& p2) {
        T radius = hyperboloid_radius(manifold);

        T form = minkowski_bilinear_form<T>(p1, p2);
        T arg = -form / (radius * radius);
        arg = std::max(arg, T{1});

        return radius * std::acosh(arg);
    }

    template<typename T>
    requires Real<T>
    T hyperbolic_angle(const Manifold<T>& manifold, const PointR3& p1, const PointR3& p2, const PointR3& p3) {
        T radius = hyperboloid_radius(manifold);

        T a = hyperbolic_distance(manifold, p2, p3);
        T b = hyperbolic_distance(manifold, p1, p2);
        T c = hyperbolic_distance(manifold, p1, p3);

        T cosh_a = std::cosh(a / radius);
        T cosh_b = std::cosh(b / radius);
        T cosh_c = std::cosh(c / radius);
        T sinh_a = std::sinh(a / radius);
        T sinh_b = std::sinh(b / radius);

        T cos_angle = (cosh_a * cosh_b - cosh_c) / (sinh_a * sinh_b);
        cos_angle = std::clamp(cos_angle, T{-1}, T{1});

        return std::acos(cos_angle);
    }

    template<typename T>
    requires Real<T>
    PointR3 hyperbolic_geodesic_point(const Manifold<T>& manifold, const PointR3& p1, const PointR3& p2, T t) {
        T radius = hyperboloid_radius(manifold);

        T form = minkowski_bilinear_form<T>(p1, p2);
        T arg = -form / (radius * radius);
        arg = std::max(arg, T{1});
        T omega = std::acosh(arg);

        if (omega < static_cast<T>(TOLERANCE)) {
            return p1;
        }

        T sinh_omega = std::sinh(omega);
        T coeff1 = std::sinh((T{1} - t) * omega) / sinh_omega;
        T coeff2 = std::sinh(t * omega) / sinh_omega;

        Vector3d result = p1 * static_cast<double>(coeff1) + p2 * static_cast<double>(coeff2);

        T norm_form = minkowski_bilinear_form<T>(result, result);
        T scale = radius / std::sqrt(-norm_form);

        return result * static_cast<double>(scale);
    }

    template<typename T>
    requires Real<T>
    PointR3 poincare_disk_projection(const Manifold<T>& manifold, const PointR3& p) {
        T radius = hyperboloid_radius(manifold);
        double denom = p[Z] + static_cast<double>(radius);

        if (std::fabs(denom) < static_cast<double>(TOLERANCE)) {
            throw std::runtime_error("Degenerate projection: point too close to boundary");
        }

        return PointR3(p[X] / denom, p[Y] / denom, 0.0);
    }

    template double minkowski_bilinear_form<double>(const PointR3&, const PointR3&);
    template bool is_on_hyperboloid<double>(const Manifold<double>&, const PointR3&, double);
    template double hyperbolic_distance<double>(const Manifold<double>&, const PointR3&, const PointR3&);
    template double hyperbolic_angle<double>(const Manifold<double>&, const PointR3&, const PointR3&, const PointR3&);
    template PointR3 hyperbolic_geodesic_point<double>(const Manifold<double>&, const PointR3&, const PointR3&, double);
    template PointR3 poincare_disk_projection<double>(const Manifold<double>&, const PointR3&);

}