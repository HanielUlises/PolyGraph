#pragma once

#include "Vector.hpp"

#include <list>
#include <vector>
#include <memory>
#include <concepts>
#include <iostream>

template <typename T>
concept Real = std::floating_point<T>;

template <Real T, size_t dim>
struct Vertex {
    bool is_ear = false;
    bool is_processed = false;

    GeomCore::Vector<T, dim> point;

    std::shared_ptr<Vertex<T, dim>> next;
    std::weak_ptr<Vertex<T, dim>> prev;

    Vertex(const GeomCore::Vector<T, dim>& p)
        : point(p), next(nullptr), prev() {}
};

template <Real T, size_t dim = R3>
class Polygon {
    private:
        std::vector<std::shared_ptr<Vertex<T, dim>>> vertex_list;

    public:
        Polygon(const std::list<GeomCore::Vector<T, dim>>& points) {
            size_t size = points.size();

            if (size < 3) {
                std::cerr << "Not enough points to construct a polygon\n";
                return;
            }

            for (const auto& p : points) {
                vertex_list.push_back(std::make_shared<Vertex<T, dim>>(p));
            }

            for (size_t i = 0; i < size; i++) {
                auto& current = vertex_list[i];
                auto& next = vertex_list[(i + 1) % size];
                auto& prev = vertex_list[(i + size - 1) % size];

                current->next = next;
                current->prev = prev;
            }
        }

        const std::vector<std::shared_ptr<Vertex<T, dim>>> &get_vertices() const {
            return vertex_list;
        }

        size_t size() const {
            return vertex_list.size();
        }

        std::shared_ptr<Vertex<T, dim>> operator[](size_t i) const {
            return vertex_list[i];
        }
};

// bool collinear(const PointR3& a, const PointR3& b, const PointR3& c);
bool is_convex(const std::shared_ptr<VertexR2>& a,
               const std::shared_ptr<VertexR2>& b,
               const std::shared_ptr<VertexR2>& c)
{
    const auto& pa = a->point;
    const auto& pb = b->point;
    const auto& pc = c->point;

    // Compute 2D cross product:
    // (b - a) x (c - b)
    double cross =
        (pb[0] - pa[0]) * (pc[1] - pb[1]) -
        (pb[1] - pa[1]) * (pc[0] - pb[0]);

    // For counter-clockwise polygons:
    // cross > 0 => convex
    return cross > 0.0;
}

using VertexR2 = Vertex<double, 2>;
using VertexR3 = Vertex<double, 3>; 

using PolygonR2 = Polygon<double, 2>;
using PolygonR3 = Polygon<double, 3>;