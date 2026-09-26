#include <cmath>
#pragma once
#include "math1.hpp"
#include "bs.hpp"

double blackScholes(double S, double K, double T, double r, double sigma, bool isCall) {
    double d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
    double d2 = d1 - sigma * sqrt(T);
    
    if (isCall) {
        return S * N(d1) - K * exp(-r * T) * N(d2);
    } else {
        return K * exp(-r * T) * N(-d2) - S * N(-d1);
    }
}
Greeks computeGreeks(double S, double K, double T, double r, double sigma, bool isCall) {
    double d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
    double d2 = d1 - sigma * sqrt(T);

    Greeks g;
    g.gamma = n(d1) / (S * sigma * sqrt(T));
    g.vega  = S * n(d1) * sqrt(T) / 100.0;

    if (isCall) {
        g.delta = N(d1);
        g.theta = (-S * n(d1) * sigma / (2 * sqrt(T)) - r * K * exp(-r * T) * N(d2)) / 365.0;
        g.rho   = K * T * exp(-r * T) * N(d2) / 100.0;
    } else {
        g.delta = N(d1) - 1.0;
        g.theta = (-S * n(d1) * sigma / (2 * sqrt(T)) + r * K * exp(-r * T) * N(-d2)) / 365.0;
        g.rho   = -K * T * exp(-r * T) * N(-d2) / 100.0;
    }

    return g;
}

    




