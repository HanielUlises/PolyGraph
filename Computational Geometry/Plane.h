#pragma once

#include "Vector.h"
#include "Point.h"

namespace GeomCore{
    template <class coord_type>
    class Plane{
            Vector3f normal;
            float d = 0;
        public:
            Plane(){}

            Plane(Vector3f &_normal, float _constant) : normal(_normal), d(_constant) {
                normal.normalize();
            }

            Plane(Point3d &_p1, Point3d &_p2, Point3d &_p3){
                auto v12 = _p2 - _p1;
                auto v13 = _p3 - _p1;

                normal = cross_product_R3(v12, v13);
                normal.normalize();
                d = dot_product(normal, _p1);
            }

            Vector3f get_normal() const {
                return normal
            }
    };

    typedef Plane<float> Plane_f;
}