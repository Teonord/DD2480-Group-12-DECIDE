#include "../include/decide.hpp"

Comptype doubleCompare (double a, double b) {
    if (fabs(a-b) < 0.000001) return EQ;
    if (a < b) return LT;
    return GT;
}
