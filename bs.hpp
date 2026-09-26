#pragma once
#include "math1.hpp"
struct Greeks {
    double delta, gamma, theta, vega, rho;
};
double blackScholes(double S, double K, double T, double r, double sigma, bool isCall);
Greeks computeGreeks(double S, double K, double T, double r, double sigma, bool isCall);