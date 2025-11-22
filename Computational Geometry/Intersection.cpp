#include "Core.h"
#include "Intersection.h"
#include "GeoUtils.h"

/**
 * @brief Determines whether two line segments AB and CD intersect (properly or improperly).
 *
 * This function implements the classic orientation-based line segment intersection test.
 * Two segments intersect if and only if:
 *  1. The endpoints of each segment lie on opposite sides (or on) the line defined by the other segment, OR
 *  2. At least one endpoint lies on the other segment (degenerate/collinear cases).
 *
 * @param a, b   Endpoints of the first segment AB
 * @param c, d   Endpoints of the second segment CD
 * @return true  if the segments intersect (including touching at endpoints or overlapping), false otherwise
 */
bool GeomCore::intersection(const Point2d& a, const Point2d& b,
                            const Point2d& c, const Point2d& d)
{
    // Compute the oriented position (orientation) of points C and D with respect to directed line AB
    auto ab_c = orientation_2d(a, b, c);   // ccw(a,b,c) ∈ {LEFT, RIGHT, BETWEEN, ORIGIN, DESTINATION}
    auto ab_d = orientation_2d(a, b, d);

    // Compute the oriented position of points A and B with respect to directed line CD
    auto cd_a = orientation_2d(c, d, a);
    auto cd_b = orientation_2d(c, d, b);

    // Degenerate cases: any endpoint lies on the other segment.
    // BETWEEN  → point is strictly inside the segment (not including endpoints)
    // ORIGIN   → point coincides with the segment's start
    // DESTINATION → point coincides with the segment's end
    // These cases are considered intersections in most geometric engines (touching/overlapping).
    if (ab_c == BETWEEN || ab_c == ORIGIN || ab_c == DESTINATION ||
        ab_d == BETWEEN || ab_d == ORIGIN || ab_d == DESTINATION ||
        cd_a == BETWEEN || cd_a == ORIGIN || cd_a == DESTINATION ||
        cd_b == BETWEEN || cd_b == ORIGIN || cd_b == DESTINATION)
    {
        return true;   // At least one endpoint lies on the opposite segment → intersection
    }

    // Proper intersection test (non-collinear case):
    // The segments straddle each other iff the orientations of C and D w.r.t. AB differ,
    // and the orientations of A and B w.r.t. CD differ.
    // Using XOR on the predicate "is strictly left of the directed line" captures exactly this condition.
    return _xor(ab_c == LEFT, ab_d == LEFT) &&      // C and D are on opposite sides of line AB
           _xor(cd_a == LEFT, cd_b == LEFT);       // A and B are on opposite sides of line CD
}

/**
 * @brief Computes the intersection point of two infinite lines defined by segments AB and CD.
 *        Only succeeds when the lines are not parallel (or coincident).
 *
 * Mathematical formulation:
 *   Line 1: P(t) = A + t·(B−A)
 *   Line 2: Q(s) = C + s·(D−C)
 *
 *   Solving P(t) = Q(s) leads to a 2×2 linear system.
 *   Here we use the projection method with normal vector to CD:
 *       n = (D−C)⊥ = (Cy−Dy, Dx−Cx)   (rotated 90° counterclockwise)
 *       denominator = n · (B−A)
 *   If denominator ≠ 0, the lines are not parallel, and parameter t is:
 *       t = [n · (C−A)] / [n · (B−A)]
 *
 * @param a,b          Endpoints defining the first line (segment AB)
 * @param c,d          Endpoints defining the second line (segment CD)
 * @param[out] intersection  The computed intersection point (valid only on success)
 * @return true if the lines are not parallel and an intersection exists, false otherwise
 */
bool GeomCore::intersection(const Point2d& a, const Point2d& b,
                            const Point2d& c, const Point2d& d,
                            Point2d& _intersection)
{
    Vector2f AB = b - a;          // Direction vector of first line
    Vector2f CD = d - c;          // Direction vector of second line

    // Normal vector to CD (rotated 90° CCW): n = (CD.y, -CD.x)
    Vector2f n(CD[Y], -CD[X]);

    // Scalar projection denominator: n · AB
    // If zero → AB ∥ CD (lines parallel or anti-parallel)
    auto denominator = dot_product(n, AB);

    if (is_equal_1D(denominator, 0.0f))   // Parallel (or coincident) lines
    {
        return false;
    }

    // Vector from A to C
    auto AC = c - a;

    // Numerator: n · (C−A)
    auto numerator = dot_product(n, AC);

    // Parameter t along line AB where intersection occurs
    auto t = numerator / denominator;

    // Parametric evaluation: intersection point = A + t·(B−A)
    auto x = a[X] + t * AB[X];
    auto y = a[Y] + t * AB[Y];

    _intersection.assign(X, x);
    _intersection.assign(Y, y);

    return true;   // Unique intersection point found
}

/**
 * @brief Convenience wrapper: intersection of two infinite Line2d objects.
 *
 * Converts each Line2d into a directed segment (start point + direction vector)
 * and forwards to the parametric line-line intersection routine above.
 *
 * @param l1, l2               The two infinite lines
 * @param[out] _intersection  Computed intersection point (valid only on true return)
 * @return true if lines intersect at a single point, false if parallel/coincident
 */
bool GeomCore::intersection(const Line2d& l1, const Line2d& l2,
                            Point2d& _intersection)
{
    auto l1_start = l1.get_point();
    auto l1_end   = l1_start + l1.get_direction();

    auto l2_start = l2.get_point();
    auto l2_end   = l2_start + l2.get_direction();

    return intersection(l1_start, l1_end, l2_start, l2_end, _intersection);
}

bool GeomCore::intersection(const Line3d& line, const Plane_f& plane, Point3d& point) {
    auto n = plane.get_normal();
    auto D = plane.get_d();
    auto d = line.get_direction();
    auto p = line.get_point();   

    auto nd = dot_product(n, d);

    if(!is_equal_1D(nd, 0)){
        auto t = (-1 * dot_product(n, p) + D) / nd;
        point.assign(X, p[X] + t * d[X]);
        point.assign(Y, p[Y] + t * d[Y]);
        point.assign(Z, p[Z] + t * d[Z]);

        return true;
    } else {
        return false;
    }
}

bool GeomCore::intersection(const Plane_f& p1, const Plane_f& p2, Line3d& l){
    Vector3f n1 = p1.get_normal();
    Vector3f n2 = p2.get_normal();
    
    float d1 = p1.get_d();
    float d2 = p2.get_d();

    auto direction = cross_product_R3(n1, n2);

    if(is_equal_1D(direction.magnitude(), 0)){
        return false;
    }

    auto n1n2 = dot_product(n1, n2);
    auto n1n2_2 = n1n2 * n1n2;

    auto a = (d2 * n1n2 - d1)/(n1n2_2 - 1);
    auto b = (d1 * n1n2 - d2)/(n1n2_2 - 1);

    auto point = n1 * a + n2 * b;

    l.set_point(point);
    direction.normalize();
    l.set_direction(direction);

    return true;
}