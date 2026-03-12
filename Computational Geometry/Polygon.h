#pragma once

#include "Vector.h"

#include <list>
#include <memory>
#include <concepts>

template <typename T>
concept Real = std::floating_point<T>;

template <class T, size_t dim>
struct Vertex {
    GeomCore::Vector<T, dim> point;
    std::shared_ptr<Vertex<T, dim>> next;
    std::weak_ptr<Vertex<T, dim>> prev;

    Vertex(GeomCore::Vector<T, dim> &_point, std::shared_ptr<Vertex<T,dim>> _next, std::weak_ptr<Vertex<T, dim>> _prev) :
        point(_point), next(std::move(_next)), prev(std::move(_prev))   {}
};

template <class T, size_t dime = R3>
requires Real<T>
class Polygon {
        std::vector<Vertex<T, dim>> vertex_list;
    public:
        Polygon(std::list<GeomCore::Vector<T,dim>> &points) {
            const int size = points.size();

            if(size < 3) {
                std::cout << "Not enough points to construct a polygon" << std::endl;
            }

            for (auto _point: points) 
                vertex_list.emplace_back(Vertex(_point));
            
            for(size_t i = 0; i < size; i++) {
                vertex_list[i].next = &vertex_list[(i + 1) % size];
                
                if(i != 0) 
                    vertex_list[i].prev = &vertex_list[i - 1];
                else
                    vertex_list[i].prev = &vertex_list[size - 1];
            }
                
        }

};

typedef Polygon<Real, 2> PolygonS2d;
typedef Polygon<Real, 3> PolygonS3d;