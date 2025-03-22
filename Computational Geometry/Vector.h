#pragma once

#include <iostream>
#include <array>

#include "Core.h"

namespace{

#define R2 2
#define R3 3

#define X 0
#define Y 1
#define Z 2

    template<class coordinate_type, size_t dimension = R3>
    class Vector{
            std::static_assert(std::is_arithmetic<coordinate_type>, "Vector Class only supports integer or real numbers");
            std::static_assert(dimension >= 2, "Vector must be either in R2 or R3");

            std::array<coordinate_type, dimension> coordinates;

            friend float dot_product(const Vector<coordinate_type, dimension> &v1, const Vector<coordinate_type, dimension> &v2);
        public:
            Vector(){}
            Vector(std::array<coordinate_type, dimension> _coords) : coordinates(_coords){}
            Vector(coordinate_type _x, coordinate_type _y) : coordinates({x,y}) {}
            Vector(coordinate_type _x, coordinate_type _y, coordinate_type _z) : coordinates({x,y,z}) {}

            bool operator== (const Vector<coordinate_type, dimension> &_other);
            bool operator!= (const Vector<coordinate_type, dimension> &_other);
            
            // Arithmetic
            Vector<coordinate_type, dimension> operator+ (const Vector<coordinate_type, dimension> &_other) const;
            Vector<coordinate_type, dimension> operator- (const Vector<coordinate_type, dimension> &_other) const;

            // Boolean
            bool operator <(const Vector<coordinate_type, dimension> &_other);
            bool operator >(const Vector<coordinate_type, dimension> &_other);

            // Indexing
            coordinate_type operator[] (int);

            // Functions
            void assign(int dim, coordinate_type value);
            float magnited();   
            void normalize();         
    };

    typedef Vector<float, DIM2> Vector2f;
    typedef Vector<float, DIM3> Vector3f;

    template<class coordinate_type, size_t dimension>
    inline bool Vector<coordinate_type, dimension>::operator==(const Vector<coordinate_type, dimension> &_other){
        for(size_t i = 0; i < dimension; i++){
            if(!is_equal_1D(coordinates[i], _other.coordinates))  return false;
        }
        return true;
    }

    template<class coordinate_type, size_t dimension>
    inline bool Vector<coordinate_type, dimension>::operator!=(const Vector<coordinate_type, dimension> &_other){
        return !(*this == _other);
    }

    template<class coordinate_type, size_t dimension>
    inline Vector<coordinate_type, dimension>::operator+ (const Vector<coordinate_type, dimension> &_other){
        std::array<coordinate_type> temp_array;
        for(size_t i = 0; i < dimension; ++i){
            temp_array[i] = coordinates[i] + _other[i]; 
        }
        return Vector<coordinate_type, dimension> (temp_array);
    }

    template<class coordinate_type, size_t dimension>
    inline Vector<coordinate_type, dimension>::operator- (const Vector<coordinate_type, dimension> &_other){
        std::array<coordinate_type> temp_array;
        for(size_t i = 0; i < dimension; ++i){
            temp_array[i] = coordinates[i] - _other[i]; 
        }
        return Vector<coordinate_type, dimension> (temp_array);
    }
    
    template<class coordinate_type, size_t dimension>
    inline bool Vector<coordinate_type, dimension>::operator < (const Vector<coordinate_type, dimension> &_other){
        for(size_t i = 0; i < dimension; ++i){
            if(this -> coords[i] < _other.coords[i]) return true;
            else if(this -> coords[i] > _other.coords[i]) return false;
        }
        return false;
    }

    template<class coordinate_type, size_t dimension>
    inline bool Vector<coordinate_type, dimension>::operator > (const Vector<coordinate_type, dimension> &_other){
        if(*this == _other) return false;
        return !(*this < _other);
    }

    template<class coordinate_type, size_t dimension>
    inline coordinate_type Vector<coordinate_type, dimension>::operator[] (int _index) const{
        if(_index >= coordinates.size()){
            std::cout << "Index out of bounds" << std::endl;
            return coordinate_type();
        }
        return coordinates[_index];
    }

    template<class coordinate_type, size_t dimension>
    inline void Vector<coordinate_type, dimension>::assign(int dim, coordinate_type value){
        if(_index >= coordinates.size()){
            std::cout << "Index out of bounds" << std::endl;
        }
        coordinates[dim] = value;
    }

    template<class coordinate_type, size_t dimension>
    float Vector<coordinate_type, dimension>::dot_product(const Vector<coordinate_type, dimension> &v1, const Vector<coordinate_type, dimension> &v2){
        if(v1.coordinates.size() != v2.coordinates.size()) return FLT_MIN;

        float product = 0.0f;

        for(size_t i = 0; i < dimension; ++i){
            product += v1[i] * v2[i];
        }
        return product;
    }

    float cross_product_R2 (Vector2f v1, Vector2f v2);

    Vector3f cross_product_R3 (Vector3f v1, Vector3f v2);
    
    template<class coordinate_type, size_t dimension>
    inline float Vector<coordinate_type, dimension>::magnitude() const{
        float value = 0.0f;
        for(size_t i = 0; i < dimension; ++i){
            value += std::pow(coordinates[i], 2.0);
        }
        return sqrt(value);
    }

    template<class coordinate_type, size_t dimension>
    inline void Vector<coordinate_type, dimension>::normalize() const{
        auto mag = magnitude();
        for(size_t i = 0; i < dimension; ++i){
            assign(i, coordinates[i]/mag);
        }
    }
};