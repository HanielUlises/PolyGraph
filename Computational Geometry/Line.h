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
                dir.normalize();
                point = p1;
            }

            Vector<coord_type, dim> get_point() const ;
            Vector<coord_type, dim> get_direction() const;

            void set_direction(Vector<coord_type, dim>& _dir);
            void set_point(Vector<coord_type, dim>& _point);
    };

    typedef Line<float, R2> Line2d;
    typedef Line<float, R3> Line3d;
    
    template <class coord_type, size_t dim>
    inline Vector<coord_type, dim> Line<coord_type, dim>::get_point() const{
        return point;
    }

    template <class coord_type, size_t dim>
    inline Vector<coord_type, dim> Line<coord_type, dim>::get_direction() const{
        return point;
    }

    template <class coord_type, size_t dim>
    inline void Line<coord_type, dim>::set_direction(Vector<coord_type, dim>& _dir) {
        dir = _dir;
    }

    template <class coord_type, size_t dim>
    inline void Line<coord_type, dim>::set_point(Vector<coord_type, dim>& _point){
        point = _point;
    }
}