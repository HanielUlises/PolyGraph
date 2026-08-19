#pragma once

#include "Core.hpp"

namespace GeomCore {

    enum class GeometryKind {
        Euclidean,
        Spherical,
        Hyperbolic
    };

    template<typename T>
    requires Real<T>
    struct Curvature {
        T value;

        constexpr explicit Curvature(T k) : value(k) {}

        constexpr GeometryKind kind() const {
            if (value > T{0}) return GeometryKind::Spherical;
            if (value < T{0}) return GeometryKind::Hyperbolic;
            return GeometryKind::Euclidean;
        }
    };

    template<typename T>
    requires Real<T>
    struct Manifold {
        Curvature<T> curvature;

        constexpr explicit Manifold(Curvature<T> k) : curvature(k) {}

        constexpr GeometryKind kind() const {
            return curvature.kind();
        }
    };

    template<typename T>
    requires Real<T>
    constexpr Manifold<T> make_euclidean() {
        return Manifold<T>(Curvature<T>(T{0}));
    }

    template<typename T>
    requires Real<T>
    constexpr Manifold<T> make_spherical(T radius) {
        return Manifold<T>(Curvature<T>(T{1} / (radius * radius)));
    }

    template<typename T>
    requires Real<T>
    constexpr Manifold<T> make_hyperbolic(T radius) {
        return Manifold<T>(Curvature<T>(-T{1} / (radius * radius)));
    }

}