#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include "bs.hpp"
#include "btree.hpp"
#include "math1.hpp"

void printGreeks(const Greeks &g) {
    std :: cout << std::fixed << std::setprecision(6);
    std::cout << "  Delta: " << g.delta << "\n";
    std::cout << "  Gamma: " << g.gamma << "\n";
    std::cout << "  Theta: " << g.theta << " (per day)\n";
    std::cout << "  Vega:  " << g.vega  << " (per 1% vol)\n";
    std::cout << "  Rho:   " << g.rho   << " (per 1% rate)\n";}

int main() {

    double S = 100.0, K = 100.0, T = 1.0, r = 0.05, sigma = 0.20;

    std::cout << "=== Black-Scholes ===\n";

    double callPrice = blackScholes(S, K, T, r, sigma, true);
    double putPrice  = blackScholes(S, K, T, r, sigma, false);
    Greeks callGreeks = computeGreeks(S, K, T, r, sigma, true);
    Greeks putGreeks  = computeGreeks(S, K, T, r, sigma, false);

    std::cout << "\nEuropean Call: " << std::fixed << std::setprecision(4) << callPrice << "\n";
    printGreeks(callGreeks);

    std::cout << "\nEuropean Put:  " << putPrice << "\n";
    printGreeks(putGreeks);

    double lhspar = callPrice - putPrice;
    double rhspar = S - K*exp(-r*T); 
    std::cout << "Put Call Parity";
    std::cout << "Difference   = " << std::abs(lhspar - rhspar) << " (should be ~0)\n";

    std::cout << "\n=== Binomial Convergence (European Call) ===\n";
    std::cout << std::setw(8)  << "Steps"
              << std::setw(12) << "Binomial"
              << std::setw(12) << "BS"
              << std::setw(12) << "Error\n";

    for (int steps : {10, 50, 100, 500, 1000}) {
        double binom = binomialTree(S, K, T, r, sigma, steps, true, false);
        std::cout << std::setw(8)  << steps
                  << std::setw(12) << std::setprecision(5) << binom
                  << std::setw(12) << callPrice
                  << std::setw(12) << std::abs(binom - callPrice) << "\n";
    }

    std::cout << "\n=== American vs European Put ===\n";
    double amPut = binomialTree(S, K, T, r, sigma, 1000, false, true);
    std::cout << "American Put:          " << std::setprecision(5) << amPut << "\n";
    std::cout << "European Put:          " << putPrice << "\n";
    std::cout << "Early exercise premium: " << (amPut - putPrice) << "\n";

    return 0;
} 

    

