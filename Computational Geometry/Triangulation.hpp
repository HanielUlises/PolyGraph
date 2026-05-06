#include "Polygon.hpp"
#include "GeoUtils.hpp"

namespace GeomCore {
    static void initialize_eart_status(PolygonR2 *polygon);
    void triangulate_earclipping(PolygonR2 *poly, std::vector<Edge2d> &edge_list);
    
}