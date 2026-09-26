# BS Binomial Option Pricer

C++ pricer for European and American options using Black-Scholes and a Cox-Ross-Rubinstein binomial tree. Computes option prices and Greeks from scratch with no external libraries.

## What it does

lack-Scholes** — closed-form pricing for European calls and puts. Also computes all five Greeks:
- Delta: sensitivity to spot price
- Gamma: rate of change of delta
- Theta: time decay (per day)
- Vega: sensitivity to volatility (per 1% move)
- Rho: sensitivity to interest rate (per 1% move)

Binomial Tree (CRR)** — discrete-time lattice model using up/down factors derived from volatility. Supports:
- European options (no early exercise)
- American options (early exercise at each node)

Convergence table shows binomial price approaching BS as steps increase (10 → 1000). American put is priced against its European equivalent to isolate the early exercise premium.

**Put-Call Parity check** — verifies `C - P = S - Ke^(-rT)` holds to floating point precision.



## Parameters (hardcoded in main.cpp)

| Param | Value |
|---|---|
| S (spot) | 100 |
| K (strike) | 100 |
| T (expiry) | 1 year |
| r (rate) | 5% |
| σ (vol) | 20% |

## Sample Output

​```
European Call: 10.4506
European Put:  5.5735
Put-call parity diff: 0.000000

Binomial @ 1000 steps: 10.44858  (error: 0.00200)
American Put:          6.08960
Early exercise premium: 0.51607
​```
