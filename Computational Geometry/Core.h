#pragma once

#include <cmath>
#include <type_traits>
#include <algorithm>  
#include <cmath>   

namespace GeomCore {
    #define TOLERANCE 0.0000001

    enum class RELATIVE_POSITION {
        LEFT, RIGHT, BEHIND, BEYOND, BETWEEN, ORIGIN, DESTINATION
    };

    static bool _xor(bool x, bool y) { return x ^ y; }

    namespace detail {
        template<typename T>
        constexpr T pi_v = T(3.1415926535897932384626433832795028841971693993751L);
    }

    template<typename T>
    constexpr std::enable_if_t<std::is_floating_point_v<T>, T>
    radians_to_degrees(T radians) {
        return radians * (T(180.0) / detail::pi_v<T>);
    }

    template<typename T>
    constexpr std::enable_if_t<std::is_floating_point_v<T>, T>
    degrees_to_radians(T degrees) {
        return degrees * (detail::pi_v<T> / T(180.0));
    }

    template<typename T> constexpr T rad2deg(T r) { return radians_to_degrees(r); }
    template<typename T> constexpr T deg2rad(T d) { return degrees_to_radians(d); }
}