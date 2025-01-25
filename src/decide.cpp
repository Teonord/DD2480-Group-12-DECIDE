#include "../include/decide.hpp"

Comptype doubleCompare (double a, double b) {
    if (fabs(a-b) < 0.000001) return EQ;
    if (a < b) return LT;
    return GT;
}

// LIC 0

// LIC 1

// LIC 2

// LIC 3

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

// LIC 8

// LIC 9

// LIC 10

// LIC 11

// LIC 12

// LIC 13

// LIC 14

// LIC 15