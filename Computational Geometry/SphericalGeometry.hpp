#pragma once

#include "Core.hpp"
#include "Manifold.hpp"
#include "Point.hpp"

namespace GeomCore {

    template<typename T>
    requires Real<T>
    T spherical_distance(const Manifold<T>& manifold, const PointR3& p1, const PointR3& p2);

    template<typename T>
    requires Real<T>
    T spherical_angle(const Manifold<T>& manifold, const PointR3& p1, const PointR3& p2, const PointR3& p3);

    template<typename T>
    requires Real<T>
    PointR3 spherical_geodesic_point(const Manifold<T>& manifold, const PointR3& p1, const PointR3& p2, T t);

    template<typename T>
    requires Real<T>
    bool is_on_sphere(const Manifold<T>& manifold, const PointR3& p, T tolerance = static_cast<T>(TOLERANCE));

}