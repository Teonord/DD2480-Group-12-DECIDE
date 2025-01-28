#define CATCH_CONFIG_MAIN

#include "../external/catch.hpp"
#include "../include/decide.hpp"

// Tests for doubleCompare

TEST_CASE( "Rounded double comparison (doubleCompare)", "[doubleCompare]") {
    REQUIRE( doubleCompare(0, 0) == EQ);
    REQUIRE( doubleCompare(-10, -10) == EQ);
    REQUIRE( doubleCompare(7, 7) == EQ);

    REQUIRE( doubleCompare(-99999, 99999) == LT);
    REQUIRE( doubleCompare(0, 1) == LT);
    REQUIRE( doubleCompare(0, 0.000001) == LT);
    
    REQUIRE( doubleCompare(99999, -99999) == GT);
    REQUIRE( doubleCompare(1, 0) == GT);
    REQUIRE( doubleCompare(0.000001, 0) == GT);

    REQUIRE( doubleCompare(0, 0.0000001) == EQ);
    REQUIRE( doubleCompare(0.0000001, 0) == EQ);
}

// Tests for LIC 0

TEST_CASE("negative distance", "[isConsecDistGTLen]") {
    Parameters_t params;
    params.NUMPOINTS = 2;
    params.LENGTH1 = -1;
    params.X = new double[2]{0, 1};
    params.Y = new double[2]{0, 0};

    REQUIRE(isConsecDistGTLen(params) == false);
}

TEST_CASE("too few points LIC 0", "[isConsecDistGTLen]") {
    Parameters_t params;
    params.NUMPOINTS = 1;
    params.LENGTH1 = 1;
    params.X = new double[1]{0};
    params.Y = new double[1]{0};

    REQUIRE(isConsecDistGTLen(params) == false);
}

TEST_CASE("2 points, dist longer than length1", "[isConsecDistGTLen]") {
    Parameters_t params;
    params.NUMPOINTS = 2;
    params.LENGTH1 = 1;
    params.X = new double[2]{0, 1};
    params.Y = new double[2]{0, 1};

    REQUIRE(isConsecDistGTLen(params) == true);
}

TEST_CASE("three points distances less than length1", "[isConsecDistGTLen]") {
    Parameters_t params;
    params.NUMPOINTS = 3;
    params.LENGTH1 = 1;
    params.X = new double[3]{0, 0.5, 1};
    params.Y = new double[3]{0, 0.5, 1};

    REQUIRE(isConsecDistGTLen(params) == false);
}

TEST_CASE("three points distances eq to length1", "[isConsecDistGTLen]") {
    Parameters_t params;
    params.NUMPOINTS = 3;
    params.LENGTH1 = 1;
    params.X = new double[3]{0, sqrt(1/2), sqrt(1/2) + sqrt(1/2)};
    params.Y = new double[3]{0, sqrt(1/2), sqrt(1/2) + sqrt(1/2)};

    REQUIRE(isConsecDistGTLen(params) == false);
}

TEST_CASE("almost within length", "[isConsecDistGTLen]") { //should be within length as within tolerance 10^-6
    Parameters_t params;
    params.NUMPOINTS = 3;
    params.LENGTH1 = 1;
    params.X = new double[3]{0, 0, 0};
    params.Y = new double[3]{0, 1.000001, 2.000002};

    REQUIRE(isConsecDistGTLen(params) == false);
}

TEST_CASE("point 4-5 outside of length", "[isConsecDistGTLen]") {
    Parameters_t params;
    params.NUMPOINTS = 5;
    params.LENGTH1 = 1;
    params.X = new double[5]{0, 0, 1, 2, 0};
    params.Y = new double[5]{0, 1, 1, 1, 0};

    REQUIRE(isConsecDistGTLen(params) == true);
}

// Tests for LIC 3
TEST_CASE("less points than required", "[lic3]") {
    Parameters_t params;
    params.NUMPOINTS = 2;
    params.AREA1 = 8;
    params.X = new double[2]{10,10};
    params.Y = new double[2]{10,10};

    REQUIRE(lic3(params) == false);
}

TEST_CASE("AREA1 too small", "[lic3]") {
    Parameters_t params;
    params.NUMPOINTS = 3;
    params.AREA1 = -1;
    params.X = new double[3]{0, 0, 1};
    params.Y = new double[3]{0, 2, 0};

    REQUIRE(lic3(params) == false);
}

TEST_CASE("negative values in points", "[lic3]") {
    Parameters_t params; 
    params.NUMPOINTS = 3;
    params.AREA1 = 2;
    params.X = new double[3]{0, 0, -2};
    params.Y = new double[3]{0, -3, 0};

    REQUIRE(lic3(params) == true);
}

TEST_CASE("precisely equal area", "[lic3]") {
    Parameters_t params;
    params.NUMPOINTS = 5;
    params.AREA1 = 5;
    params.X = new double[5]{0, 1, 2, 2, 7};
    params.Y = new double[5]{0, 1, 0, 2, 2};

    REQUIRE(lic3(params) == false);
}

TEST_CASE("too small area of triangle", "[lic3]") {
    Parameters_t params;
    params.NUMPOINTS = 5;
    params.AREA1 = 5;
    params.X = new double[5]{0, 1, 2, 3, 4};
    params.Y = new double[5]{0, 0.5, 0, 0.5, 0};

    REQUIRE(lic3(params) == false);
}

TEST_CASE("area big enough", "[lic3]") {
    Parameters_t params;
    params.NUMPOINTS = 5;
    params.AREA1 = 2;
    params.X = new double[5]{0, 10, 15, 20, 43};
    params.Y = new double[5]{5, 0, 10, 13, 2};

    REQUIRE(lic3(params) == true);
}

// Tests for LIC 5

TEST_CASE("LIC 5: Not enough points", "[lic5]") {
    Parameters_t params;
    params.NUMPOINTS = 1;
    params.X = new double[1]{1.0};
    params.Y = new double[1]{1.0};

    REQUIRE(lic5(params) == false); // Not enough points
}

TEST_CASE("LIC 5: No consecutive decreasing x-coordinates", "[lic5]") {
    Parameters_t params;
    params.NUMPOINTS = 4;
    params.X = new double[4]{1.0, 2.0, 3.0, 4.0};
    params.Y = new double[4]{1.0, 1.0, 1.0, 1.0};

    REQUIRE(lic5(params) == false); // No consecutive decreasing xgit 
}

TEST_CASE("LIC 5: One pair of consecutive decreasing x-coordinates", "[lic5]") {
    Parameters_t params;
    params.NUMPOINTS = 4;
    params.X = new double[4]{4.0, 3.0, 5.0, 6.0};
    params.Y = new double[4]{1.0, 1.0, 1.0, 1.0};

    REQUIRE(lic5(params) == true); // One pair satisfies condition
}

TEST_CASE("LIC 5: Multiple pairs of consecutive decreasing x-coordinates", "[lic5]") {
    Parameters_t params;
    params.NUMPOINTS = 5;
    params.X = new double[5]{5.0, 3.0, 4.0, 2.0, 1.0};
    params.Y = new double[5]{1.0, 1.0, 1.0, 1.0, 1.0};

    REQUIRE(lic5(params) == true); // Multiple pairs satisfy condition
}


// Tests for LIC 6

TEST_CASE("too few points", "[isDistFromLine]") {
    Parameters_t params;
    params.NUMPOINTS = 2;
    params.N_PTS = 3;
    params.DIST = 1.0;
    params.X = new double[2]{0, 1};
    params.Y = new double[2]{0, 0};

    REQUIRE(isDistFromLine(params) == false);
}

TEST_CASE("base line w/o dev", "[isDistFromLine]") {
    Parameters_t params;
    params.NUMPOINTS = 5;
    params.N_PTS = 3;
    params.DIST = 2.0;
    params.X = new double[5]{0, 1, 2, 3, 4};
    params.Y = new double[5]{0, 0, 0, 0, 0};

    REQUIRE(isDistFromLine(params) == false);
}

TEST_CASE("base line w/ dev", "[isDistFromLine]") {
    Parameters_t params;
    params.NUMPOINTS = 5;
    params.N_PTS = 3;
    params.DIST = 1.0;
    params.X = new double[5]{0, 1, 2, 3, 4};
    params.Y = new double[5]{0, 1.5, 0, 0, 0};

    REQUIRE(isDistFromLine(params) == true);
}

TEST_CASE("point w/o dev", "[isDistFromLine]") {
    Parameters_t params;
    params.NUMPOINTS = 4;
    params.N_PTS = 4;
    params.DIST = 2.0;
    params.X = new double[4]{0, 1, 2, 0};
    params.Y = new double[4]{0, 0, 0, 0};  // Almost a straight line

    REQUIRE(isDistFromLine(params) == false);
}

TEST_CASE("point w/ dev", "[isDistFromLine]") {
    Parameters_t params;
    params.NUMPOINTS = 4;
    params.N_PTS = 4;
    params.DIST = 1.0;
    params.X = new double[4]{0, 1, 2, 0};
    params.Y = new double[4]{0, 1, 2, 0};

    REQUIRE(isDistFromLine(params) == true);
}

TEST_CASE("line exactly on dist", "[isDistFromLine]") {
    Parameters_t params;
    params.NUMPOINTS = 3;
    params.N_PTS = 3;
    params.DIST = 1.0;
    params.X = new double[3]{0, 1, 2};
    params.Y = new double[3]{0, 1, 0}; 

    REQUIRE(isDistFromLine(params) == false);
}

TEST_CASE("almost within", "[isDistFromLine]") {
    Parameters_t params;
    params.NUMPOINTS = 4;
    params.N_PTS = 3;
    params.DIST = 1.0;
    params.X = new double[4]{0, 1, 2, 3};
    params.Y = new double[4]{0, 1.00000001, 0, 0};  // Should be equal according to doubleCompare

    REQUIRE(isDistFromLine(params) == false);
}

TEST_CASE("line w/ negative doubles", "[isDistFromLine]") {
    Parameters_t params;
    params.NUMPOINTS = 4;
    params.N_PTS = 3;
    params.DIST = 2.0;
    params.X = new double[4]{-1, 0, 1, 2};
    params.Y = new double[4]{-1, 0, 1, 2};

    REQUIRE(isDistFromLine(params) == false);
}

TEST_CASE("points within circle", "[sepPointsCointainedInCircle]") {
    Parameters_t params;
    params.NUMPOINTS = 5;
    params.A_PTS = 1;
    params.B_PTS = 1;
    params.RADIUS1 = 5.0;
    params.X = new double[5]{0, 1, 2, 3, 4};
    params.Y = new double[5]{0, 1, 2, 3, 4};  

    REQUIRE(sepPointsContainedInCircle(params) == false);
}

TEST_CASE("points outside circle", "[sepPointsCointainedInCircle]") {
    Parameters_t params;
    params.NUMPOINTS = 6;
    params.A_PTS = 2;
    params.B_PTS = 1;
    params.RADIUS1 = 2.0;
    params.X = new double[6]{0, 1, 5, 6, 8, 10};
    params.Y = new double[6]{0, 1, 5, 6, 8, 10}; 

    REQUIRE(sepPointsContainedInCircle(params) == true);
}

TEST_CASE("triangle fits within circle", "[sepPointsCointainedInCircle]") {
    Parameters_t params;
    params.NUMPOINTS = 5;
    params.A_PTS = 1;
    params.B_PTS = 1;
    params.RADIUS1 = 3.0;
    params.X = new double[5]{0, 1, 2, 2, 3};
    params.Y = new double[5]{0, 1, 1.5, 1, 0};

    REQUIRE(sepPointsContainedInCircle(params) == false);
}

TEST_CASE("triangle exceeds circle", "[sepPointsCointainedInCircle]") {
    Parameters_t params;
    params.NUMPOINTS = 5;
    params.A_PTS = 1;
    params.B_PTS = 1;
    params.RADIUS1 = 1.5;
    params.X = new double[5]{0, 1, 2, 5, 6};
    params.Y = new double[5]{0, 1, 4, 5, 6}; 

    REQUIRE(sepPointsContainedInCircle(params) == true);
}

TEST_CASE("collinear points within circle", "[sepPointsCointainedInCircle]") {
    Parameters_t params;
    params.NUMPOINTS = 6;
    params.A_PTS = 2;
    params.B_PTS = 1;
    params.RADIUS1 = 5.0;
    params.X = new double[6]{0, 2, 4, 6, 8, 10};
    params.Y = new double[6]{0, 0, 0, 0, 0, 0}; 

    REQUIRE(sepPointsContainedInCircle(params) == false);
}

TEST_CASE("boundary condition - on the edge of the circle", "[sepPointsCointainedInCircle]") {
    Parameters_t params;
    params.NUMPOINTS = 5;
    params.A_PTS = 1;
    params.B_PTS = 1;
    params.RADIUS1 = 2.0;
    params.X = new double[5]{0, 2, 4, 1, 3};
    params.Y = new double[5]{0, 2, 0, 1, 1}; 

    REQUIRE(sepPointsContainedInCircle(params) == false);
}

// Tests for LIC 9
TEST_CASE("C_PTS under threshold", "[isAngleWithinThreshold]") {
    Parameters_t params;
    params.C_PTS = 0;
    params.D_PTS = 1;
    params.NUMPOINTS = 5; 
    params.EPSILON = -PI;
    params.X = new double[5]{1, 1, 0, 1, 0};
    params.Y = new double[5]{0, 2, 0, 1, 1};

    REQUIRE(isAngleWithinThreshold(params) == false);
}

TEST_CASE("D_PTS under threshold", "[isAngleWithinThreshold]") {
    Parameters_t params;
    params.C_PTS = 1;
    params.D_PTS = 0;
    params.NUMPOINTS = 5; 
    params.EPSILON = -PI;
    params.X = new double[5]{1, 2, 0, 1, 0};
    params.Y = new double[5]{0, 2, 0, 1, 1};

    REQUIRE(isAngleWithinThreshold(params) == false);
}

TEST_CASE("Numpoints under threshold", "[isAngleWithinThreshold]") {
    Parameters_t params;
    params.C_PTS = 1;
    params.D_PTS = 0;
    params.NUMPOINTS = 3; 
    params.EPSILON = -PI;
    params.X = new double[5]{1, 2, 0, 1, 0};
    params.Y = new double[5]{0, 2, 0, 1, 1};

    REQUIRE(isAngleWithinThreshold(params) == false);
}

TEST_CASE("90 degree angle, LT 180 allowed", "[isAngleWithinThreshold]") {
    Parameters_t params;
    params.C_PTS = 1;
    params.D_PTS = 1;
    params.NUMPOINTS = 5; 
    params.EPSILON = 0;
    params.X = new double[5]{1, 2, 0, 1, 0};
    params.Y = new double[5]{0, 2, 0, 1, 1};

    REQUIRE(isAngleWithinThreshold(params) == true);
}

TEST_CASE("90 degree angle, LT 90 allowed", "[isAngleWithinThreshold]") {
    Parameters_t params;
    params.C_PTS = 1;
    params.D_PTS = 1;
    params.NUMPOINTS = 5; 
    params.EPSILON = PI / 2;
    params.X = new double[5]{1, 2, 0, 1, 0};
    params.Y = new double[5]{0, 2, 0, 1, 1};

    REQUIRE(isAngleWithinThreshold(params) == false);
}


// Tests for LIC 10
TEST_CASE("E_PTS and F_PTS below allowed threshold", "[lic10]") {
    Parameters_t params;
    params.E_PTS = 0;
    params.F_PTS = 0;
    params.NUMPOINTS = 5; 
    params.AREA1 = 1;
    params.X = new double[5]{0, 2, 4, 1, 3};
    params.Y = new double[5]{0, 2, 0, 1, 1};

    REQUIRE(lic10(params) == false);
}

TEST_CASE("E PTS + F PTS > NUMPOINTS - 3, this is not allowed", "[lic10]") {
    Parameters_t params;
    params.E_PTS = 2;
    params.F_PTS = 3;
    params.NUMPOINTS = 7; 
    params.AREA1 = 1;
    params.X = new double[7]{0, 2, 4, 1, 3, 4, 5};
    params.Y = new double[7]{0, 2, 0, 1, 1, 4, 5};

    REQUIRE(lic10(params) == false);
}

TEST_CASE("NUMPOINTS < 5, not allowed", "[lic10]") {
    Parameters_t params;
    params.E_PTS = 2;
    params.F_PTS = 2;
    params.NUMPOINTS = 4; 
    params.AREA1 = 1;
    params.X = new double[4]{100, 0, 2, 1};
    params.Y = new double[4]{0, 2, 0, 1};

    REQUIRE(lic10(params) == false);
}

TEST_CASE("edge case: the area of the triangle is equal to AREA1", "[lic10]") {
    Parameters_t params;
    params.E_PTS = 2;
    params.F_PTS = 2;
    params.NUMPOINTS = 8; 
    params.AREA1 = 12;
    params.X = new double[8]{0, 1, 2, 12, 3, 12, 0, 4};
    params.Y = new double[8]{0, 2, 2, 0, 2, 0, 2, 2};

    REQUIRE(lic10(params) == false);
}

TEST_CASE("negative values, scenario should be ok", "[lic10]") {
    Parameters_t params;
    params.E_PTS = 2;
    params.F_PTS = 2;
    params.NUMPOINTS = 8; 
    params.AREA1 = 20;
    params.X = new double[8]{-100, 0, 2, 0, 1, 12, -50, 2};
    params.Y = new double[8]{0, -1, 3, 100, 0, 32, 50, -2};

    REQUIRE(lic10(params) == true);
}

TEST_CASE("allowed scenario", "[lic10]") {
    Parameters_t params;
    params.E_PTS = 2;
    params.F_PTS = 2;
    params.NUMPOINTS = 8; 
    params.AREA1 = 20;
    params.X = new double[8]{100, 0, 2, 0, 1, 12, 50, 2};
    params.Y = new double[8]{0, 1, 3, 100, 0, 32, 50, 2};

    REQUIRE(lic10(params) == true);
}

// Tests for LIC 11
TEST_CASE("G_PTS too small", "[lic11]") {
    Parameters_t params;
    params.G_PTS = 0;
    params.NUMPOINTS = 3;
    params.X = new double[3]{3, 2, 1};

    REQUIRE(lic11(params) == false);
}

TEST_CASE("G_PTS too large", "[lic11]") {
    Parameters_t params;
    params.G_PTS = 2;
    params.NUMPOINTS = 3;
    params.X = new double[3]{3, 2, 1};

    REQUIRE(lic11(params) == false);
}

TEST_CASE("X[i] = X[j], not allowed", "[lic11]") {
    Parameters_t params;
    params.G_PTS = 1;
    params.NUMPOINTS = 3;
    params.X = new double[3]{1, 1, 1};

    REQUIRE(lic11(params) == false);
}

TEST_CASE("NUMPOINTS < 3, not allowed", "[lic11]") {
    Parameters_t params;
    params.G_PTS = 1;
    params.NUMPOINTS = 2;
    params.X = new double[2]{1, 1};

    REQUIRE(lic11(params) == false);
}

TEST_CASE("negative values, should not be allowed", "[lic11]") {
    Parameters_t params;
    params.G_PTS = 1;
    params.NUMPOINTS = 5;
    params.X = new double[5]{1, -3, 2, 2, 3};

    REQUIRE(lic11(params) == false);
}

TEST_CASE("both negative values, should not be allowed", "[lic11]") {
    Parameters_t params;
    params.G_PTS = 1;
    params.NUMPOINTS = 5;
    params.X = new double[5]{1, -3, 2, -2, 3};

    REQUIRE(lic11(params) == false);
}

TEST_CASE("negative values, should be allowed", "[lic11]") {
    Parameters_t params;
    params.G_PTS = 1;
    params.NUMPOINTS = 5;
    params.X = new double[5]{1, 3, 2, -4, 3};

    REQUIRE(lic11(params) == true);
}

TEST_CASE("appropriate scenario, should be allowed", "[lic11]") {
    Parameters_t params;
    params.G_PTS = 1;
    params.NUMPOINTS = 5;
    params.X = new double[5]{1, 5, 2, 4, 3};

    REQUIRE(lic11(params) == true);
}

// Tests for LIC 14
TEST_CASE("E_PTS and F_PTS too small", "[lic14]") {
    Parameters_t params;
    params.E_PTS = 0;
    params.F_PTS = 0;
    params.NUMPOINTS = 5; 
    params.AREA1 = 12;
    params.AREA2 = 12;
    params.X = new double[5]{0, 2, 4, 1, 3};
    params.Y = new double[5]{0, 2, 0, 1, 1};

    REQUIRE(lic14(params) == false);
}

TEST_CASE("NUMPOINTS too small", "[lic14]") {
    Parameters_t params;
    params.E_PTS = 1;
    params.F_PTS = 1;
    params.NUMPOINTS = 4; 
    params.AREA1 = 12;
    params.AREA2 = 12;
    params.X = new double[4]{100, 0, 2, 1};
    params.Y = new double[4]{0, 2, 0, 1};

    REQUIRE(lic14(params) == false);
}

TEST_CASE("AREA2 too small", "[lic14]") {
    Parameters_t params;
    params.E_PTS = 1;
    params.F_PTS = 1;
    params.NUMPOINTS = 5; 
    params.AREA1 = 12;
    params.AREA2 = 0;
    params.X = new double[5]{100, 0, 2, 1, 1};
    params.Y = new double[5]{0, 2, 0, 1, 2};

    REQUIRE(lic14(params) == false);
}

TEST_CASE("A > AREA1 fulfilled; A < AREA2 not fulfilled", "[lic14]") {
    Parameters_t params;
    params.E_PTS = 1;
    params.F_PTS = 1;
    params.NUMPOINTS = 5; 
    params.AREA1 = 12;
    params.AREA2 = 12;
    params.X = new double[5]{100, 0, 1, 1, 1};
    params.Y = new double[5]{0, 2, 100, 1, 5};

    REQUIRE(lic14(params) == false);
}

TEST_CASE("A > AREA1 not fulfilled; A < AREA2 fulfilled", "[lic14]") {
    Parameters_t params;
    params.E_PTS = 1;
    params.F_PTS = 1;
    params.NUMPOINTS = 5; 
    params.AREA1 = 12;
    params.AREA2 = 12;
    params.X = new double[5]{0, 0, 1, 1, 2};
    params.Y = new double[5]{0, 2, 0, 1, 0};

    REQUIRE(lic14(params) == false);
}

TEST_CASE("edge case: A = AREA1", "[lic14]") {
    Parameters_t params;
    params.E_PTS = 1;
    params.F_PTS = 2;
    params.NUMPOINTS = 6; 
    params.AREA1 = 12;
    params.AREA2 = 12;
    params.X = new double[6]{0, 100, 0, 12, 12, 12};
    params.Y = new double[6]{0, 2, 2, 12, 13, 0};

    REQUIRE(lic14(params) == false);
}

TEST_CASE("edge case: A = AREA2", "[lic14]") {
    Parameters_t params;
    params.E_PTS = 2;
    params.F_PTS = 2;
    params.NUMPOINTS = 7; 
    params.AREA1 = 12;
    params.AREA2 = 3;
    params.X = new double[7]{0, 0, 100, 6, 2, 1, 0};
    params.Y = new double[7]{0, 2, 0, 0, 1, 1, 1};

    REQUIRE(lic14(params) == false);
}

TEST_CASE("negative values, ok scenario", "[lic14]") {
    Parameters_t params;
    params.E_PTS = 2;
    params.F_PTS = 2;
    params.NUMPOINTS = 8; 
    params.AREA1 = 20;
    params.AREA2 = 12;
    params.X = new double[8]{-100, 0, 2, 0, 1, 12, -50, 2};
    params.Y = new double[8]{0, -1, 3, 100, 0, 32, 50, -2};

    REQUIRE(lic14(params) == true);
}

TEST_CASE("ok scenario", "[lic14]") {
    Parameters_t params;
    params.E_PTS = 2;
    params.F_PTS = 2;
    params.NUMPOINTS = 8; 
    params.AREA1 = 20;
    params.AREA2 = 12;
    params.X = new double[8]{100, 0, 2, 0, 1, 12, 50, 2};
    params.Y = new double[8]{0, 1, 3, 100, 0, 32, 50, 2};

    REQUIRE(lic14(params) == true);
}