#include "Polygon.hpp"
#include "GeoUtils.hpp"
#include "Edge.hpp"

namespace GeomCore {
    static void initialize_eart_status(PolygonR2 *polygon);
    void triangulate_earclipping(PolygonR2 *poly, std::vector<EdgeR2> &edge_list);
}