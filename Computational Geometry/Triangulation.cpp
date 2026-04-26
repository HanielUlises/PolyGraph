#include "Triangulation.hpp"

void GeomCore::initialize_eart_status(PolygonR2 *polygon) {
    VertexR2 *v0, *v1, *v2;
    auto vertices = polygon -> get_vertices();
    v1 = vertices[0].get();

    do {
        v0 = v1 -> prev.lock().get();
        v2 = v1 -> next.get();

        if(is_convex(v0, v1, v2))
            v1 -> is_ear = is_diagonal(std::make_shared<VertexR2> (v0), std::make_shared<VertexR2> (v2));
        v1 = v1 -> next.get();
    } while(v1 != vertices[0].get());
}