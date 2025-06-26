#include "Vector.h"

namespace GeomCore{
    template <class coord_type, size_t dim = R3>
    class Line{
        Vector<coord_type, dim> point;
        Vector<coord_type, dim> dir;
    };    
}