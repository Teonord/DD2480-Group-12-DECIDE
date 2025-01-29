#include "../include/decide.hpp"
#include <array>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


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

/** LIC 0
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

/* LIC 1
 * Checks if there exists at least one pair of consecutive points where the distance between them
 * is greater than the diameter (2 * RADIUS1) of a circle.
 * The function iterates through consecutive points, calculates the distance between each pair,
 * and compares it to 2 * RADIUS1.
 * It returns true if at least one pair satisfies the condition, otherwise false.
 */

bool lic1(Parameters_t params) {
    if (params.NUMPOINTS < 2) {
        return false; // Not enough points to evaluate
    }

    for (int i = 0; i < params.NUMPOINTS - 1; ++i) {
        double x1 = params.X[i], y1 = params.Y[i];
        double x2 = params.X[i + 1], y2 = params.Y[i + 1];

        // Calculate the distance between the two points
        double distance = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));

        // Check if the distance is greater than 2 * RADIUS1 (diameter of the circle)
        if (distance > 2 * params.RADIUS1) {
            return true; // Found a pair of points that cannot fit within the circle
        }
    }

    return false; // No such pair of points found
}



/* LIC 2
 *
 * Checks if there are three consecutive points that form an angle outside the range [PI - EPSILON, PI + EPSILON].
 * The function iterates through the points and calculates the angle between two vectors formed by three consecutive points.
 * It uses the dot product formula and magnitudes of the vectors to compute the angle.
 * The function returns true if at least one angle is less than (PI - EPSILON) or greater than (PI + EPSILON).
 * Collinear points with an angle exactly equal to PI are ignored.
 */
bool lic2(Parameters_t params) {
    if (params.NUMPOINTS < 3) {
        return false; // Not enough points to form an angle
    }

    for (int i = 0; i <= params.NUMPOINTS - 3; ++i) {
        double x1 = params.X[i], y1 = params.Y[i];
        double x2 = params.X[i + 1], y2 = params.Y[i + 1];
        double x3 = params.X[i + 2], y3 = params.Y[i + 2];

        // Vectors from the middle point to the other two points
        double vector1_x = x1 - x2;
        double vector1_y = y1 - y2;
        double vector2_x = x3 - x2;
        double vector2_y = y3 - y2;

        // Magnitudes of the vectors
        double magnitude1 = std::sqrt(vector1_x * vector1_x + vector1_y * vector1_y);
        double magnitude2 = std::sqrt(vector2_x * vector2_x + vector2_y * vector2_y);

        // Skip collinear points (magnitude == 0)
        if (magnitude1 == 0 || magnitude2 == 0) {
            continue;
        }

        // Compute the dot product and the angle
        double dot_product = (vector1_x * vector2_x + vector1_y * vector2_y);
        double cos_theta = dot_product / (magnitude1 * magnitude2);

        // Clamp cos_theta to [-1, 1] to account for floating-point precision errors
        cos_theta = std::max(-1.0, std::min(1.0, cos_theta));

        double angle = std::acos(cos_theta); // Angle in radians

        // Check if the angle is outside the range [PI - EPSILON, PI + EPSILON]
        if (angle < (M_PI - params.EPSILON) || angle > (M_PI + params.EPSILON)) {
            return true; // Found an angle outside the range
        }
    }

    return false; // No such angle found
}


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

bool lic4(Parameters_t params){

    if(params.QUADS < 1 || params.QUADS > 3 || params.Q_PTS < 2 || params.Q_PTS > params.NUMPOINTS) return false;

    for(int j = 0; j <= params.NUMPOINTS - params.Q_PTS; j++){
        bool quad[4] = {false, false, false, false};
        for(int i = j; i < j + params.Q_PTS; i++){
            if(params.Y[i] >= 0){
                if(params.X[i] >= 0){
                    quad[0] = true;
                } else {
                    quad[1] = true;
                }
            } else {
                if(params.X[i] <= 0){
                    quad[2] = true;
                } else {
                    quad[3] = true;
                }
            }
        }
        int count = 0;
        for(int i = 0; i < 4; i++){
            if(quad[i]) count++;
        }
        if(params.QUADS < count) return true;
    }

    return false;
        
}

/* LIC 5
 *
 * This code solves LIC 5, which is true if there exists at least one pair of consecutive data points
 * where the x-coordinate of the first point is greater than the x-coordinate of the second point. 
 * If there are fewer than 2 points, the condition cannot be satisfied, and the function returns false. 
 */
bool lic5(Parameters_t params) {
    if (params.NUMPOINTS < 2) {
        return false; // Not enough points to compare
    }

    for (int i = 0; i < params.NUMPOINTS - 1; ++i) {
        if (params.X[i] > params.X[i + 1]) {
            return true; // Condition satisfied
        }
    }

    return false; // No such pair found
}


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
/* 
 * This code solves LIC 7, it iterates through pairs of points separated by K_PTS consequtive points until it finds 
 * two points with a distance larger than LENGTH1 between them and returns true, or untill it has iterated 
 * through all possible pairs of points separated by K_PTS and returns false.
 */
 bool lic7(Parameters_t params) {
    if(params.LENGTH1 <= 0 || params.NUMPOINTS <3 || params.K_PTS < 1 || params.K_PTS > params.NUMPOINTS - 2) return false;

    for(int i = 0; i < params.NUMPOINTS - params.K_PTS - 1; i++){
        // https://www.khanacademy.org/math/geometry/hs-geo-analytic-geometry/hs-geo-distance-and-midpoints/v/distance-formula
        // d=√((x_2-x_1)²+(y_2-y_1)²)
        double dst = sqrt(pow(params.X[i + params.K_PTS + 1] - params.X[i], 2) + pow(params.Y[i + params.K_PTS + 1] - params.Y[i], 2));
        if(doubleCompare(dst, params.LENGTH1) == GT) return true;
    }
    return false;
 }

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

/**  LIC 9
 * Determines if the angle between two vectors exceeds a specified threshold.
 *
 * This function checks if the angle formed by three points (A, B, and C) exceeds the threshold
 * defined by PI - EPSILON. It iterates through the list of points and calculates
 * the angle using the dot product formula. The function returns true if the angle is less
 * than (PI - EPSILON)
 *
 * @param params A Parameters_t object containing the following fields:
 *               - C_PTS: The number of consecutive intervening points between the first point (A) and the second point (B).
 *               - D_PTS: The number of consecutive intervening points between the second point (B) and the third point (C).
 *               - NUMPOINTS: The total number of points.
 *               - EPSILON: The angle threshold in radians.
 *               - X: An array of X-coordinates of the points.
 *               - Y: An array of Y-coordinates of the points.
 * 
 * @return boolean: Returns true if any angle is within the threshold, otherwise returns false.
 */
bool isAngleWithinThreshold(Parameters_t params) {
    // Base Cases (implicitly returns false if NUMPOINTS < 5)
    if (params.C_PTS < 1 || params.D_PTS < 1 || params.C_PTS + params.D_PTS > params.NUMPOINTS - 3) return false;
    if (params.EPSILON > PI || params.EPSILON < 0) return false;

    for(int i = 0; i < params.NUMPOINTS - params.C_PTS - params.D_PTS - 2; i++){
        int A = i;
        int B = i + params.C_PTS + 1;
        int C = i + params.C_PTS + params.D_PTS + 2;

        //continue if point A or C are EQ to point B (vertex)
        if(doubleCompare(params.X[A], params.X[B]) == EQ && doubleCompare(params.Y[A], params.Y[B]) == EQ) continue;
        if(doubleCompare(params.X[B], params.X[C]) == EQ && doubleCompare(params.Y[B], params.Y[C]) == EQ) continue;

        //calculate vector 2(B)->1(A) and 2(B)->3(C), vector B->A => A_i-B_i
        double vectBAx = params.X[A] - params.X[B];
        double vectBAy = params.Y[A] - params.Y[B];
        double vectBCx = params.X[C] - params.X[B];
        double vectBCy = params.Y[C] - params.Y[B];

        //https://en.wikipedia.org/wiki/Dot_product
        //angle = arctan (dot product / ||v1|| * ||v2||)
        double dotproduct = vectBAx * vectBCx + vectBAy * vectBCy;
        double vectBAmagnitude = sqrt(pow(vectBAx, 2) + pow(vectBAy, 2));
        double vectBCmagnitude = sqrt(pow(vectBCx, 2) + pow(vectBCy, 2));
        double angle = acos(dotproduct/vectBAmagnitude * vectBCmagnitude); //angle in rads

        if(doubleCompare(angle, PI - params.EPSILON) == LT) return true;
        if(doubleCompare(angle, PI + params.EPSILON) == GT) return true; // not really necessary as the angle calculated will be shortest distance between the vectors.
    }

    // If nothing was found
    return false;

}

// LIC 10
/* This code solves LIC10
 *
 * It iterates throgh the datapoints and if the area with the three specified points are larger then AREA1, the function returns true.
 * Otherwise it returns false.
 */
bool lic10(Parameters_t params){
     if(params.NUMPOINTS < 5 || params.E_PTS < 1 || params.F_PTS < 1 || params.AREA1 <= 0
        || params.E_PTS + params.F_PTS > params.NUMPOINTS - 3) return false;

     for(int i = 0; i < params.NUMPOINTS - params.E_PTS - params.F_PTS - 2; i++){
          int second = i + params.E_PTS + 1;
          int third = second + params.F_PTS + 1;
          // determinant formula: https://www.cuemath.com/geometry/area-of-triangle-in-determinant-form/
          double area = 0.5 * std::abs(
            params.X[i]*(params.Y[second] - params.Y[third]) + 
            params.X[second]*(params.Y[third]-params.Y[i]) + 
            params.X[third]*(params.Y[i]) - params.Y[second]);
          if(doubleCompare(area, params.AREA1) == GT) return true;
     }
     return false;
}

// LIC 11
/* This code solces LIC11
 *
 * It iterates through the give datapoints and compares if x value of the datapoint at i + G_PTS is less than -
 * (LT) the x value of the datpoint at i.
 * If this comparison is true, at any point, we know that the conditions of X[j]-X[i]<0 and i<j will be satisfied.
 * It returns false if no such comparison is found.
 */
bool lic11(Parameters_t params) {
    if(params.NUMPOINTS < 3 || params.G_PTS < 1 || params.G_PTS > params.NUMPOINTS - 2) return false;

    for(int i = 0; i < params.NUMPOINTS - params.G_PTS - 1; i++){  
        if(params.X[i + params.G_PTS + 1] - params.X[i] < 0) return true;
    }
    return false;
}

/**  LIC 12
 *
 * This function checks whether there are a pair of points separated by K_PTS that are further than LENGTH1
 * distance from eachother. It also checks whether there are a pair of points separated by K_PTS that are 
 * closer than LENGTH2 distance from eachother. These may be the same or different points. Both criteria
 * have to be filled for the function to return true.
 *
 * @param params A Parameters_t object with the following important fields:
 *              - K_PTS: The number of consecutive intervening points between the first point and the second point.
 *              - NUMPOINTS: The total number of points.
 *              - LENGTH1: The length that two points must be more distant than.
 *              - LENGTH2: The length that two points must be less distant than.
 *              - X: An array of X-coordinates of the points.
 *              - Y: An array of Y-coordinates of the points.
 *
 * @return boolean: true if both criteria stated above are filled, otherwise false. 
 */
 bool lic12(Parameters_t params) {

    // Base Cases
    if(params.NUMPOINTS < 3 || params.K_PTS < 1 || params.LENGTH1 < 0 || params.LENGTH2 < 0) return false;

    bool gtL1 = false;
    bool gtL2 = false;

    for (int i = 0; i < params.NUMPOINTS - params.K_PTS - 1; i++) {
        double length = hypot(params.X[i + params.K_PTS + 1] - params.X[i], params.Y[i + params.K_PTS + 1] - params.Y[i]);
        if (doubleCompare(length, params.LENGTH1) == GT) {
            gtL1 = true;
            if (gtL2) return true;
        }

        if (doubleCompare(length, params.LENGTH2) == LT) {
            gtL2 = true;
            if (gtL1) return true;
        }
    }

    return false;
 }

/**  LIC 13
 * 
 * This function checks if there are three points seperated by exactly A_PTS and B_PTS 
 * consecutive intervening. For any three points separeted by the intervening point.
 * It checks if there are any three points that do not fit into a circle of radius = RADIUS1
 * It also checks if there are any three points that do fit into a circle of radius = RADIUS2
 * If both conditions are met it returns true.
 * If only one or none are met it returns false
 *
 * @param params A Parameters_t object containing the following fields:
 *              - A_PTS: The number of consecutive intervening points between the first point and the second point.
 *              - B_PTS: The number of consecutive intervening points between the second point and the third point.
 *              - NUMPOINTS: The total number of points.
 *              - RADIUS1: double radius of a circle.
 *              - RADIUS2: double radius of a circle.
 *              - X: An array of X-coordinates of the points.
 *              - Y: An array of Y-coordinates of the points.
 * 
 * @return boolean: Returns true if any three separate points fit in radius2 AND if any three
 * separe points CANNOT fit in radius1 else return false
 */

bool lic13(Parameters_t params) {
    // Base Cases (implicitly returns false if NUMPOINTS < 5)
    if (params.A_PTS < 1 || params.B_PTS < 1 || params.A_PTS + params.B_PTS > params.NUMPOINTS - 3) return false;

    bool radius1Condition = false;
    bool radius2Condition = false;
    
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
        
        // Calculate Circumradius 
        // https://artofproblemsolving.com/wiki/index.php/Circumradius
        // https://www.cuemath.com/geometry/area-of-triangle-in-coordinate-geometry/
        double area = fabs(ax * (by-cy) + bx * (cy-ay) + cx * (ay-by)) / 2;
        if (doubleCompare(area, 0) == EQ) continue;
        double circumradius = (ab * bc * ac) / (4 * area);

        if (doubleCompare(circumradius, params.RADIUS1) == GT) radius1Condition = true; //Assuming they fit if EQ to radius
        if (doubleCompare(circumradius, params.RADIUS2) != GT) radius2Condition = true; //Assuming they fit if EQ to radius
    }

    if (radius1Condition && radius2Condition) return true;
    return false;
}

// LIC 14
/* This code solves LIC14
 *
 * It iterates throgh the datapoints and if the criteria for AREA1 is fulfilled the a1 boolean is set to true,
 * and if the criteria for AREA2 is fulfilled the a2 boolean is set to true.
 * After iterating through all points, if criteria for both AREA1 and AREA2 is fulfilled, the function returns true.
 * Otherwise it returns false.
 */
bool lic14(Parameters_t params){
     if(params.NUMPOINTS < 5 || params.AREA1 <= 0 || params.AREA2 <= 0) return false;

     bool a1 = false;
     bool a2 = false;
     for(int i = 0; i < params.NUMPOINTS - params.E_PTS - params.F_PTS - 2; i++){
          int second = i + params.E_PTS + 1;
          int third = second + params.F_PTS + 1;
          // determinant formula: https://www.cuemath.com/geometry/area-of-triangle-in-determinant-form/
          double area = 0.5 * std::abs(
            params.X[i]*(params.Y[second] - params.Y[third]) + 
            params.X[second]*(params.Y[third]-params.Y[i]) + 
            params.X[third]*(params.Y[i]) - params.Y[second]);
          if(doubleCompare(area, params.AREA1) == GT) a1 = true;
          if(doubleCompare(area, params.AREA2) == LT) a2 = true;
     }
     if(a1 && a2) return true;
     return false;
}
/** generatePreliminaryUnlockingMatrix
 * This code generates the PUV matrix of bools, which is based on the LCM and the CMV. Depending on which
 * logical operator is on a spot in the LCM, the program will check the CMV to know whether the output matrix
 * should have TRUE or FALSE on that location. For LCM[x][y] NOTUSED means the result will always be true. ORR means 
 * that the returned [x][y] will be true if either CMV[x] or CMV[y] is true. ANDD means that the returned [x][y] will
 * be true if both CMV[x] and CMV[y] is true. Points where x == y are always true.
 *
 * @param CMV Conditions Met Vector, vector containing the LCMs that are fulfilled
 * @param LCM Logical Connector Matrix, a 15x15 symmetrical matrix which contains logical operators
 *            to decide the resulting bool in the returned matrix
 * 
 * @return boolean matrix: 15x15 symmetrical matrix where each point is true or false depending
 *         on the combination of the CMV and the LCM. Diagonal is always true.
 */
std::array<std::array<bool, 15>, 15> generatePreliminaryUnlockingMatrix(std::array<bool, 15> CMV, std::array<std::array<Connectors, 15>, 15> LCM) {
    std::array<std::array<bool, 15>, 15> retMatrix;
    for (int y = 0; y < 15; y++) {
        for (int x = 0; x < 15; x++) {
            if (x == y) {
                retMatrix[y][x] = true;
                continue;
            }

            switch (LCM[y][x])
            {
            case NOTUSED:
                retMatrix[y][x] = true;
                break;
            
            case ORR:
                if(CMV[x] || CMV[y]) retMatrix[y][x] = true;
                else retMatrix[y][x] = false;
                break;
            
            case ANDD:
                if(CMV[x] && CMV[y]) retMatrix[y][x] = true;
                else retMatrix[y][x] = false;
                break;
            }
        }
    }
    return retMatrix;
}

/** generateFinalUnlockingVector 
 * This code generates the vector that will make the decision launch/no launch from the combination of the PUM and a Preliminary
 * Unlocking Vector which decides which of the rows in the PUM that are important for the launch decision. If an index in PUV is
 * false, the whole row of the same index in PUM is ignored and index in FUV is true. If index in PUV is true, then whole row in
 * PUM has to be true for the FUV index to be true.
 * 
 * @param PUM Preliminary Unlocking Matrix, generated from the combination of the solved LICs and the LCM
 * @param PUV Preliminary Unlocking Vector, decides which rows of the PUM that should be taken account of.alignas
 * 
 * @return Final Unlocking Vector, 15 index vector of bools that will ultimately decide launch/no launch
*/
std::array<bool, 15> generateFinalUnlockingVector(std::array<std::array<bool, 15>, 15> PUM, std::array<bool, 15> PUV) {
    std::array<bool, 15> FUV; 
    for (int i = 0; i < 15; i++) {
        if (PUV[i] == false) {
            FUV[i] = true;
            continue;
        }
        bool allTrue = true;
        for (int j = 0; j < 15; j++) {
            if (PUM[i][j] == false) {
                allTrue = false;
                break;
            }
        }
        FUV[i] = allTrue;
    }
    return FUV;
}

/** launchDecision
 * This code checks whether launch should go ahead or not. Launch is allowed when all
 * objects in FUV is true, otherwise it is not. 
 *
 * @param FUV Final Unlocking Vector, all indices have to be true to return true
 * 
 * @return boolean: true if and only if all indices in FUV are true. 
 */
bool launchDecision(bool FUV[15]) {
    bool launch = true;
    for (int i = 0; i < 15; i++) {
        if (!FUV[i]) {
            launch = false;
            break;
        }
    }
    return launch;
}