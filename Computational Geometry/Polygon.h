#pragma once

#include "Vector.h"

#include <list>
#include <vector>
#include <memory>
#include <concepts>
#include <iostream>

template <typename T>
concept Real = std::floating_point<T>;

template <Real T, size_t dim>
struct Vertex {
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

        size_t size() const {
            return vertex_list.size();
        }

        std::shared_ptr<Vertex<T, dim>> operator[](size_t i) const {
            return vertex_list[i];
        }
};

using PolygonS2d = Polygon<double, 2>;
using PolygonS3d = Polygon<double, 3>;