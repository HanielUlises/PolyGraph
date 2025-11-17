#include "GeoUtils.h"

double GeomCore::area_triangle_2d(const Point2d &a, const Point2d &b, const Point2d &c){
    auto AB = b - a;
    auto AC = c - a;

    auto result = cross_product_R2(AB, AC);
    return result / 2;
}

int GeomCore::orientation_2d(const Point2d &a, const Point2d &b, const Point2d &c){
    auto area = area_triangle_2d(a, b, c);
    
    if(area > 0 && area < TOLERANCE)
        area = 0;
    else if(area > 0 && area > TOLERANCE)
        area = 0;


    Vector2f ab = b - a;
    Vector2f ac = a - c;
    
    if(area > 0)
        return LEFT;
    else if(area < 0)
        return RIGHT;
    else if ((ab[X] * ac[X] < 0) || (ab[Y] * ac[Y] < 0))
        return BEHIND; 

    if(ab.magnitude() < ac.magnitude())
        return BEYOND;
    else if (a == c)
        return ORIGIN;
    else if (b == c)
        return DESTINATION;

    return BETWEEN;
}

/**
 * Checks whether two 3D vectors a and b are collinear (parallel or anti-parallel),
 * including the degenerate cases where one or both vectors are zero.
 *
 * Mathematically, vectors a, b ∈ ℝ³ are collinear if and only if their cross
 * product vanishes:
 *     a × b = 0
 *
 * The cross product in ℝ³ is defined component-wise as:
 *     (a × b)_x = a_y b_z - a_z b_y
 *     (a × b)_y = a_z b_x - a_x b_z
 *     (a × b)_z = a_x b_y - a_y b_x
 *
 * This condition is equivalent to a and b being linearly dependent over ℝ.
 * A small floating-point tolerance is applied via is_equal_1D(·, 0) to account
 * for numerical errors in floating-point arithmetic.
 *
 * Note: The zero vector is considered collinear with every vector (including itself).
 */
bool GeomCore::collinear(const Vector3f& a, const Vector3f& b){
    auto v1 = a[X] * b[Y] - a[Y] * b[X];
    auto v2 = a[Y] * b[Z] - a[Z] * b[Y];
    auto v3 = a[X] * b[Z] - a[Z] * b[X];

    return is_equal_1D(v1, 0.0f) && is_equal_1D(v2, 0.0f) && is_equal_1D(v3, 0.0f);
}

/**
 * Tests whether three points A, B, C are collinear.
 *
 * Points A, B, C are collinear iff vectors AB and AC are parallel, i.e.
 *     AB × AC = 0
 *
 * This is implemented by computing the direction vectors from A and reusing
 * the vector-based collinear() test above.
 */
bool GeomCore::collinear(const Point3d& a, const Point3d& b, const Point3d& c){
    auto AB = b - a;
    auto AC = c - a;
    return collinear(AB, AC);
}

/**
 * Checks whether three 3D vectors a, b, c are coplanar.
 *
 * Three vectors are coplanar if and only if their scalar triple product
 * (box product) vanishes:
 *     [a, b, c] = a · (b × c) = 0
 *
 * This is equivalent to the vectors being linearly dependent in ℝ³.
 * The function delegates to scaler_triple_product(), which must compute
 * the determinant of the matrix formed by the three vectors.
 */

bool GeomCore::coplaner(const Vector3f& a, const Vector3f& b, const Vector3f& c){
    float value = scaler_triple_product(a, b, c);
    return is_equal_1D(value, 0.0f);
}

/**
 * Tests whether four points A, B, C, D lie on the same plane.
 *
 * Four points are coplanar iff the vectors AB, AC, AD are coplanar, i.e.
 *     [AB, AC, AD] = AB · (AC × AD) = 0
 *
 * This condition is equivalent to the scalar triple product of the three
 * direction vectors from A being zero, or equivalently, the volume of the
 * tetrahedron formed by the four points being zero.
 */
bool GeomCore::coplaner(const Point3d& a, const Point3d& b, const Point3d& c, const Point3d& d){
    auto AB = b - a;
    auto AC = c - a;
    auto AD = d - a;

    return coplaner(AB, AC, AD);
}