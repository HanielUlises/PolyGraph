#include "Vector.h"

namespace GeomCore{
    template <class coord_type, size_t dim = R3>
    class Line{
        Vector<coord_type, dim> point;
        Vector<coord_type, dim> dir;
        
        public:
            Line(){}
            Line(Vector<coord_type, dim> &p1, Vector<coord_type, dim> &p2){
                dir = p2 - p1;
                point = p1;
            }

            Vector<coord_type, dim> get_point();
            Vector<coord_type, dim> get_direction();
    };
    
    template <class coord_type, size_t dim>
    inline Vector<coord_type, dim> Line<coord_type, dim>::get_point(){
        return point;
    }

    template <class coord_type, size_t dim>
    inline Vector<coord_type, dim> Line<coord_type, dim>::get_direction(){
        return point;
    }
}