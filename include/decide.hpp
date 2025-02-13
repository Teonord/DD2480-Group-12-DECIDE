#ifndef DECIDE_H
#define DECIDE_H

#include <cmath>
#include <array>

static const double PI = 3.1415926535;

// Enum to know operator in LCM
typedef enum { NOTUSED=777, ORR, ANDD } Connectors;

// Enum to compare values
typedef enum { LT=1111, EQ, GT } Comptype;

// Struct for inputs to DECIDE. 
typedef struct {
    int NUMPOINTS;      // Number of points
    double *X;          // X Coordinates of data points
    double *Y;          // Y Coordinates of data points
    double LENGTH1;     // Lenth in LICs 0, 7, 12
    double RADIUS1;     // Radius in LICs 1, 8, 13
    double EPSILON;     // Deviation from PI in LICs 2, 9
    double AREA1;       // Area in LICs 3, 10, 14
    int Q_PTS;          // No. of consecutive points in LIC 4
    int QUADS;          // No. of quadrants in LIC 4
    double DIST;        // Distance in LIC 6
    int N_PTS;          // No. of consecutive pts. in LIC 6
    int K_PTS;          // No. of int. pts. in LICs 7, 12
    int A_PTS;          // No. of int. pts. in LICs 8, 13
    int B_PTS;          // No. of int. pts. in LICs 8, 13
    int C_PTS;          // No. of int. pts. in LIC 9
    int D_PTS;          // No. of int. pts. in LIC 9
    int E_PTS;          // No. of int. pts. in LICs 10, 14
    int F_PTS;          // No. of int. pts. in LICs 10, 14
    int G_PTS;          // No. of int. pts. in LIC 11
    double LENGTH2;     // Max length in LIC 12
    double RADIUS2;     // Max radius in LIC 13
    double AREA2;       // Max area in LIC 14
} Parameters_t;

// Compare floating point numbers
Comptype doubleCompare (double a, double b);

// The goal DECIDE function. 
void decide();

// LIC 0
bool isConsecDistGTLen(Parameters_t params);

// LIC 1
bool lic1(Parameters_t params);

// LIC 2
bool lic2(Parameters_t params);

// LIC 3
bool lic3(Parameters_t params);

// LIC 4
bool lic4(Parameters_t params);

// LIC 5
bool lic5(Parameters_t params);

// LIC 6
bool isDistFromLine(Parameters_t params);

// LIC 7
bool lic7(Parameters_t params);

// LIC 8
bool sepPointsContainedInCircle(Parameters_t params);

// LIC 9
bool isAngleWithinThreshold(Parameters_t params);

// LIC 10
bool lic10(Parameters_t params);

// LIC 11
bool lic11(Parameters_t params);

// LIC 12
bool lic12(Parameters_t params);

// LIC 13
bool lic13(Parameters_t params);

// LIC 14
bool lic14(Parameters_t params);

// Generate PUV
std::array<std::array<bool, 15>, 15> generatePreliminaryUnlockingMatrix(std::array<bool, 15> CMV, std::array<std::array<Connectors, 15>, 15> LCM);

// Generate FUV
std::array<bool, 15> generateFinalUnlockingVector(std::array<std::array<bool, 15>, 15> PUM, std::array<bool, 15> PUV);

// Launch Decision
bool launchDecision(std::array<bool, 15> FUV);

#endif
