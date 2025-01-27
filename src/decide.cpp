#include "../include/decide.hpp"
#include <iostream>

 /**
 * Compares two double values with a precision tolerance.
 *
 * This function compares two double values `a` and `b` to determine their
 * relative difference within a specified precision tolerance of 0.000001.
 * It returns EQ if the values are nearly equal, LT if `a` is less than `b`,
 * and GT if `a` is greater than `b`.
 *
 * @param a First double value to compare.
 * @param b Second double value to compare.
 * @return CompType Comparison result: EQ, LT, or GT.
 */
Comptype doubleCompare (double a, double b) {
    if (fabs(a-b) < 0.000001) return EQ;
    if (a < b) return LT;
    return GT;
}

/* LIC 0
/*
 * Checks if there are two consecutive points with a distance greater than LENGTH1.
 *
 * This function iterates through the given points and checks if any two consecutive
 * points have a distance between them that is greater than the specified LENGTH1.
 * It returns true if such a pair of points is found, and false otherwise.
 *
 * @param params Parameters_t structure containing the number of points, their coordinates, and LENGTH1.
 * @return bool True if there are two consecutive points with a distance greater than LENGTH1, false otherwise.
 */
bool isConsecDistGTLen(Parameters_t params){
    if(params.NUMPOINTS < 2 || params.LENGTH1 < 0) return false;

    for(int i = 0; i < params.NUMPOINTS - 1; i++){
        //pythagoran theorem
        double distance = sqrt(pow(params.X[i+1] - params.X[i], 2) + pow(params.Y[i+1] - params.Y[i], 2));
        if(doubleCompare(distance, params.LENGTH1) == GT) return true;
    }

    return false;
}

// LIC 1

// LIC 2

// LIC 3
/*
 * Checks if there are three consecutive points that form a triangle with area > AREA1.
 *
 * The function iterates through the given points and uses the determinant formula to calculate area of triangle.
 * It returns true if area is greater than AREA1.
 */
bool lic3(Parameters_t params) {
    if(params.NUMPOINTS < 3 || params.AREA1 < 0) return false;

    for(int i = 0; i < params.NUMPOINTS -2; i++){
        // determinant formula: https://www.cuemath.com/geometry/area-of-triangle-in-determinant-form/
        double area = 0.5 * std::abs(
            params.X[i] * (params.Y[i+1] - params.Y[i+2]) + 
            params.X[i+1] * (params.Y[i+2]-params.Y[i]) + 
            params.X[i+2] * (params.Y[i] - params.Y[i+1]));
        if(doubleCompare(area, params.AREA1) == GT) return true;
    }
    return false;
}

// LIC 4

// LIC 5

/* LIC 6
 *
 * This code solves LIC 6, which is true if there is at least one sequence of N_PTS consecutive points where 
 * at least one of the points lies a distance greater than DIST away from the line connecting the first and
 * last of these N_PTS. If the first and last are the same, instead check distance from point. 
 */
bool isDistFromLine(Parameters_t params) {
    // Base Cases
    if (params.NUMPOINTS < 3 || params.N_PTS < 3 || params.NUMPOINTS < params.N_PTS) return false;
    for (int i = 0; i < params.NUMPOINTS - params.N_PTS + 1; i++) {

        // If both edge pos are same, calculate distance from point 
        if (doubleCompare(params.X[i], params.X[i+params.N_PTS-1]) == EQ && doubleCompare(params.Y[i], params.Y[i+params.N_PTS-1]) == EQ) {
            for(int j = i + 1; j < i + params.N_PTS - 1; j++) {
                // Pythagorean Theorem 
                double distance = sqrt(pow(params.X[j] - params.X[i], 2) + pow(params.Y[j] - params.Y[i], 2));
                
                if (doubleCompare(distance, params.DIST) == GT) return true;
            }
        } else {
            // https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line
            double a = params.Y[i+params.N_PTS-1] - params.Y[i];
            double b = params.X[i+params.N_PTS-1] - params.X[i];
            double c = params.X[i+params.N_PTS-1] * params.Y[i] - params.Y[i+params.N_PTS-1] * params.X[i];
            double denom = sqrt(pow(params.Y[i+params.N_PTS-1] - params.Y[i], 2) + pow(params.X[i+params.N_PTS-1] - params.X[i], 2));

            for(int j = i + 1; j < i + params.N_PTS - 1; j++) {
                double distance = fabs((a * params.X[j] - b * params.Y[j] + c) / denom);
                if (doubleCompare(distance, params.DIST) == GT) return true;
            }
        }
    }
    // Only reached if no point matches the requirements
    return false;
}

// LIC 7

/* LIC 8
 *
 * This code solves LIC 8, which is true if there is at least one set of three data points (with separation
 * A_PTS between 1 and 2 and B_PTS between 2 and 3) where all three points do not fit within a circle of radius
 * RADIUS1. First checks easy distances, if a distance is further than RADIUS1 * 2 we know that they can't fit.
 * Then we check distances from midpoint of the longest hypotenuse. If the point that this hypotenuse is not
 * connected to is further than RADIUS1 from the midpoint, we finally check the Circumradius to find the circle
 * which is on all 3 of the points. This is why the second check has to be done, as too close points would lead
 * to a far too large circle. Here, if the circumradius is larger than RADIUS1 we know they cannot be contained
 * within a circle of RADIUS1.
 */
bool sepPointsContainedInCircle(Parameters_t params) {
    // Base Cases (implicitly returns false if NUMPOINTS < 5)
    if (params.A_PTS < 1 || params.B_PTS < 1 || params.A_PTS + params.B_PTS > params.NUMPOINTS - 3) return false;
    
    for (int i = 0; i < params.NUMPOINTS - params.A_PTS - params.B_PTS - 2; i++) {
        double ax = params.X[i];
        double bx = params.X[i+params.A_PTS+1];
        double cx = params.X[i+params.A_PTS+params.B_PTS+2];
        double ay = params.Y[i];
        double by = params.Y[i+params.A_PTS+1];
        double cy = params.Y[i+params.A_PTS+params.B_PTS+2];

        // Make a triangle
        double ab = hypot(bx - ax, by - ay);
        double ac = hypot(cx - ax, cy - ay);
        double bc = hypot(cx - bx, cy - by);
        // If distance between two points is longer than diameter, cannot be kept within circle of radius RADIUS1
        if(ab > params.RADIUS1 * 2 || ac > params.RADIUS1 * 2 || bc > params.RADIUS1 * 2) return true;
        
        // Check if distance between midpoints of longest side and the remaining point is within RADIUS1  
        double dist;
        if(ab > ac && ab > bc) {
            double nx = (ax + bx) / 2;
            double ny = (ay + by) / 2;
            dist = hypot(cx - nx, cy - ny);
        } else if (ac > ab && ac > bc) {
            double nx = (ax + cx) / 2;
            double ny = (ay + cy) / 2;
            dist = hypot(bx - nx, by - ny);
        } else {
            double nx = (bx + cx) / 2;
            double ny = (by + cy) / 2;
            dist = hypot(ax - nx, ay - ny);
        }
        if (doubleCompare(dist, params.RADIUS1) != GT) continue;

        // Calculate Circumradius 
        // https://artofproblemsolving.com/wiki/index.php/Circumradius
        // https://www.cuemath.com/geometry/area-of-triangle-in-coordinate-geometry/
        double area = fabs(ax * (by-cy) + bx * (cy-ay) + cx * (ay-by)) / 2;
        if (doubleCompare(area, 0) == EQ) continue;
        double circumradius = (ab * bc * ac) / (4 * area);

        if (doubleCompare(circumradius, params.RADIUS1) == GT) return true;
    }

    // If nothing was found
    return false;
}

// LIC 9

// LIC 10

// LIC 11

// LIC 12

// LIC 13

// LIC 14

// LIC 15