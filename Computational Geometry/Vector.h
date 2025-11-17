#pragma once

#include <array>
#include <cmath>
#include <iostream>
#include <limits>
#include <type_traits>

#include "Core.h"

namespace GeomCore {

#define R2 2
#define R3 3

#define X 0
#define Y 1
#define Z 2

template <class coordinate_type, size_t dimension = R3>
class Vector {
    static_assert(std::is_arithmetic_v<coordinate_type>, "Vector class only supports arithmetic types (integers or floating-point numbers)");
    static_assert(dimension >= 2 && dimension <= 3, "Vector dimension must be 2 or 3");

    std::array<coordinate_type, dimension> coordinates;

    friend float dot_product(const Vector<coordinate_type, dimension>& v1, const Vector<coordinate_type, dimension>& v2);

public:
    Vector() : coordinates{} {}
    Vector(std::array<coordinate_type, dimension> coords) : coordinates(coords) {}
    
    
    Vector(coordinate_type x, coordinate_type y) {
        static_assert(dimension == 2, "This constructor is only for 2D vectors.");
        coordinates = {x, y};
    }

    Vector(coordinate_type x, coordinate_type y, coordinate_type z) {
        static_assert(dimension == 3, "This constructor is only for 3D vectors.");
        coordinates = {x, y, z};
    }

    // Comparison operators
    bool operator==(const Vector<coordinate_type, dimension>& other) const;
    bool operator!=(const Vector<coordinate_type, dimension>& other) const;

    // Arithmetic operators
    Vector<coordinate_type, dimension> operator+(const Vector<coordinate_type, dimension>& other) const;
    Vector<coordinate_type, dimension> operator-(const Vector<coordinate_type, dimension>& other) const;

    // Boolean operators
    bool operator<(const Vector<coordinate_type, dimension>& other) const;
    bool operator>(const Vector<coordinate_type, dimension>& other) const;

    // Indexing
    coordinate_type operator[](size_t index) const;
    coordinate_type& operator[](size_t index);

    // Functions
    void assign(size_t dim, coordinate_type value);
    float magnitude() const;
    void normalize();
};

using Vector2f = Vector<float, R2>;
using Vector3f = Vector<float, R3>;

inline bool is_equal_1D(double a, double b, double epsilon = 1e-5) {
    return std::fabs(a - b) <= epsilon;
}

// Implementation of comparison operators
template <class coordinate_type, size_t dimension>
inline bool Vector<coordinate_type, dimension>::operator==(const Vector<coordinate_type, dimension>& other) const {
    for (size_t i = 0; i < dimension; ++i) {
        if constexpr (std::is_floating_point_v<coordinate_type>) {
            if (!is_equal_1D(static_cast<double>(coordinates[i]), static_cast<double>(other.coordinates[i]))) {
                return false;
            }
        } else {
            if (coordinates[i] != other.coordinates[i]) {
                return false;
            }
        }
    }
    return true;
}

template <class coordinate_type, size_t dimension>
inline bool Vector<coordinate_type, dimension>::operator!=(const Vector<coordinate_type, dimension>& other) const {
    return !(*this == other);
}

// Implementation of arithmetic operators
template <class coordinate_type, size_t dimension>
inline Vector<coordinate_type, dimension> Vector<coordinate_type, dimension>::operator+(const Vector<coordinate_type, dimension>& other) const {
    std::array<coordinate_type, dimension> result;
    for (size_t i = 0; i < dimension; ++i) {
        result[i] = coordinates[i] + other.coordinates[i];
    }
    return Vector<coordinate_type, dimension>(result);
}

template <class coordinate_type, size_t dimension>
inline Vector<coordinate_type, dimension> Vector<coordinate_type, dimension>::operator-(const Vector<coordinate_type, dimension>& other) const {
    std::array<coordinate_type, dimension> result;
    for (size_t i = 0; i < dimension; ++i) {
        result[i] = coordinates[i] - other.coordinates[i];
    }
    return Vector<coordinate_type, dimension>(result);
}

template <class coordinate_type, size_t dimension>
inline bool Vector<coordinate_type, dimension>::operator<(const Vector<coordinate_type, dimension>& other) const {
    for (size_t i = 0; i < dimension; ++i) {
        if (coordinates[i] < other.coordinates[i]) return true;
        if (coordinates[i] > other.coordinates[i]) return false;
    }
    return false;
}

template <class coordinate_type, size_t dimension>
inline bool Vector<coordinate_type, dimension>::operator>(const Vector<coordinate_type, dimension>& other) const {
    if (*this == other) return false;
    return !(*this < other);
}

// Implementation of indexing operators
template <class coordinate_type, size_t dimension>
inline coordinate_type Vector<coordinate_type, dimension>::operator[](size_t index) const {
    if (index >= dimension) {
        std::cerr << "Vector index out of bounds" << std::endl;
        return coordinate_type{};
    }
    return coordinates[index];
}

template <class coordinate_type, size_t dimension>
inline coordinate_type& Vector<coordinate_type, dimension>::operator[](size_t index) {
    if (index >= dimension) {
        std::cerr << "Vector index out of bounds" << std::endl;
        throw std::out_of_range("Vector index out of bounds");
    }
    return coordinates[index];
}

template <class coordinate_type, size_t dimension>
inline void Vector<coordinate_type, dimension>::assign(size_t dim, coordinate_type value) {
    if (dim >= dimension) {
        std::cerr << "Vector dimension out of bounds" << std::endl;
        return;
    }
    coordinates[dim] = value;
}

template <class coordinate_type, size_t dimension>
inline float Vector<coordinate_type, dimension>::magnitude() const {
    float value = 0.0f;
    for (size_t i = 0; i < dimension; ++i) {
        value += static_cast<float>(coordinates[i] * coordinates[i]);
    }
    return std::sqrt(value);
}

template <class coordinate_type, size_t dimension>
inline void Vector<coordinate_type, dimension>::normalize() {
    float mag = magnitude();
    if (mag > TOLERANCE) {
        for (size_t i = 0; i < dimension; ++i) {
            coordinates[i] = static_cast<coordinate_type>(coordinates[i] / mag);
        }
    }
}

template <class coordinate_type, size_t dimension>
inline float dot_product(const Vector<coordinate_type, dimension>& v1, const Vector<coordinate_type, dimension>& v2) {
    float product = 0.0f;
    for (size_t i = 0; i < dimension; ++i) {
        product += static_cast<float>(v1.coordinates[i] * v2.coordinates[i]);
    }
    return product;
}

inline Vector3f cross_product_R3(const Vector3f& v1, const Vector3f& v2) {
    float _x = v1[Y] * v2[Z] - v1[Z] * v2[Y];
    float _y = v1[Z] * v2[X] - v1[X] * v2[Z];
    float _z = v1[X] * v2[Y] - v1[Y] * v2[X];
    return Vector3f(_x, _y, _z);
}

// Cross product 
float cross_product_R2(const Vector2f& v1, const Vector2f& v2);
Vector3f cross_product_R3(const Vector3f& v1, const Vector3f& v2);

float scaler_triple_product(const Vector3f& v1, const Vector3f& v2, const Vector3f& v3);

} // namespace GeomCore