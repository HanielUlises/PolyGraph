#include "Vector.h"

namespace jmk{
    template <class coord_type, size_t dim = DIM3>
    class Line{
        Vector<coord_type, dim> point;
        Vector<coord_type, dim> dir;
    };    
}