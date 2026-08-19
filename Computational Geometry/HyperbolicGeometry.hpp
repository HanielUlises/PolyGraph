#pragma once

#include "Core.hpp"
#include "Manifold.hpp"
#include "Point.hpp"

namespace GeomCore {

    template<typename T>
    requires Real<T>
    T minkowski_bilinear_form(const PointR3& p1, const PointR3& p2);

    template<typename T>
    requires Real<T>
    bool is_on_hyperboloid(const Manifold<T>& manifold, const PointR3& p, T tolerance = static_cast<T>(TOLERANCE));

    template<typename T>
    requires Real<T>
    T hyperbolic_distance(const Manifold<T>& manifold, const PointR3& p1, const PointR3& p2);

    template<typename T>
    requires Real<T>
    T hyperbolic_angle(const Manifold<T>& manifold, const PointR3& p1, const PointR3& p2, const PointR3& p3);

    template<typename T>
    requires Real<T>
    PointR3 hyperbolic_geodesic_point(const Manifold<T>& manifold, const PointR3& p1, const PointR3& p2, T t);

    template<typename T>
    requires Real<T>
    PointR3 poincare_disk_projection(const Manifold<T>& manifold, const PointR3& p);

}