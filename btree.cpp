#include <cmath>
#include <vector>
#include <algorithm>
#include "bs.hpp"
double binomialTree(double S, double K, double T, double r, double sigma,int 
    steps, bool isCall, bool isAmerican) { 
    double dt = T / steps;
    double u = exp(sigma * sqrt(dt));
    double d = 1.0 / u;
    double p = (exp(r * dt) - d) / (u - d);
    double disc = exp(-r * dt);

    std::vector<double> optionValues(steps + 1);

    for (int i = 0; i <= steps; i++) {
        double spotAtLeaf = S * pow(u, steps - i) * pow(d, i);
        optionValues[i] = isCall ? std::max(spotAtLeaf - K, 0.0)
                           : std::max(K - spotAtLeaf, 0.0);
    }

    for (int step = steps - 1; step >= 0; step--) {
          for (int i = 0; i <= step; i++) {
            double hold = disc * (p * optionValues[i] + (1 - p) * optionValues[i + 1]);

            if (isAmerican) {
                double spotNow = S * pow(u, step - i) * pow(d, i);
                double exercise = isCall ? std::max(spotNow - K, 0.0)
                                         : std::max(K - spotNow, 0.0);
                optionValues[i] = std::max(hold, exercise);
            } else {
                optionValues[i] = hold;
            }
        }
    }

    return optionValues[0];
}