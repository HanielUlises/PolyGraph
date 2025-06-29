#include "Vector.h"

float GeomCore::cross_product_R2(Vector2f v1, Vector2f v2){
    return v1[X] * v2 [Y] - v1[Y] * v2[X];
}

GeomCore::Vector3f GeomCore::cross_product_R3(Vector3f v1, Vector3f v2){
    float _x = v1[Y] * v2[Z] - v1[Z] * v2[Y];
    float _y = v1[Z] * v2[X] - v1[X] * v2[Z];
    float _z = v1[X] * v2[Y] - v1[Y] * v2[X];

    return Vector3f(_x, _y, _z);
}