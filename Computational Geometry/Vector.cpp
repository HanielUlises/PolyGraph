#include "Vector.h"

float jmk::cross_product_R2(Vector2f v1, Vector2f v2){
    return v1[X] * v2 [Y] - v1[Y] * v2[X];
}

jmk::Vector3f jmk::cross_product_R3(Vector3f v1, Vector3f v2){
    float _x, _y, _z;

    _x = v1[Y] * v2[Z] - v1[Z] * v2[Y];
    _y = -(v2[Z] * v1[X] * v2[X]);
    _z = v1[X] * v2[Y] - v2[X] * v1[Y];

    return Vector3f(_x, _y, _z);
}