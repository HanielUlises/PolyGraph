#pragma once

#include "Polygon.hpp"

class EdgeR2 {
private:
    std::weak_ptr<VertexR2> start_vertex;
    std::weak_ptr<VertexR2> end_vertex;

public:
    EdgeR2() = default;

    EdgeR2(const std::shared_ptr<VertexR2>& start,
           const std::shared_ptr<VertexR2>& end)
        : start_vertex(start), end_vertex(end) {}

    std::shared_ptr<VertexR2> start() const {
        return start_vertex.lock();
    }

    std::shared_ptr<VertexR2> end() const {
        return end_vertex.lock();
    }

    GeomCore::Vector<double, 2> direction() const {
        auto s = start_vertex.lock();
        auto e = end_vertex.lock();

        if (!s || !e) {
            throw std::runtime_error("Invalid edge vertices");
        }

        return e->point - s->point;
    }

    template <typename T>
    T length() const {
        return direction().normalize();
    }

    bool is_valid() const {
        return !start_vertex.expired() &&
               !end_vertex.expired();
    }
};