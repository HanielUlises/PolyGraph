#include "Vector.hpp"

float GeomCore::cross_product_R2(const Vector2d &v1, const Vector2d &v2){
    return v1[X] * v2 [Y] - v1[Y] * v2[X];
}

GeomCore::Vector3d GeomCore::cross_product_R3(const Vector3d& v1,const Vector3d& v2){
    float _x = v1[Y] * v2[Z] - v1[Z] * v2[Y];
    float _y = v1[Z] * v2[X] - v1[X] * v2[Z];
    float _z = v1[X] * v2[Y] - v1[Y] * v2[X];

    return Vector3d(_x, _y, _z);
}

float GeomCore::scaler_triple_product(const Vector3d& v1, const Vector3d& v2, const Vector3d& v3){
    auto bc_cros = cross_product_R3(v2, v3);
    return dot_product(v1, bc_cros);
}