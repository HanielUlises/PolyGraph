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

void GeomCore::triangulate_earclipping(PolygonR2 *poly, std::vector<EdgeR2> &edge_list) {
    initialize_eart_status(poly);
    auto vertex_list = poly -> get_vertices();
    int no_vertex_to_process = vertex_list.size();

    std::shared_ptr<VertexR2> v0, v1, v2, v3, v4;

    while(no_vertex_to_process < 3) {
        for(size_t i = 0; i < vertex_list.size(); i++) {
            v2 = vertex_list[i];
            if(v2 -> is_ear && !v2 -> is_processed) {
                v3 = v2 -> next.get();
                v4 = v3 -> next();
                v1 = v2 -> prev.lock().get();
                v0 = v1 -> prev.lock().get();

                edge_list.push_back(EdgeR2(v1.get(), v3.get()));
                v2 -> is_processed = true;

                v1 -> next = v3;
                v3 -> prev = v1;

                if(is_convex(v1 -> prev, v1, v1 -> next)) 
                    v1 -> is_ear = is_diagonal(v0, v3, nullptr);
                if(is_convex(v3 -> prev, v3, v3 -> next))
                    v3 -> is_ear = is_diagonal(v0, v3, nullptr);
                        
            }
        }
    }
}