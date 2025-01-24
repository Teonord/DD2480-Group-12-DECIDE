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