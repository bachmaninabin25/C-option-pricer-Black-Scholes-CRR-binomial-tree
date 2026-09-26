#include <cmath>
#pragma once

double N(double x) {
   return 0.5 * erfc(-x / sqrt(2.0));
}

double n(double x) {
    return exp(-0.5*x*x) / sqrt(2*3.141592653589793);
}


