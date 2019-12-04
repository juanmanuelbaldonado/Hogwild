#ifndef SCORE_HPP
#define SCORE_HPP

#include <cmath>
#include <iostream>
#include "estimator.hpp"

class Scorer {
public:
    unsigned int n;         /* Sample size */
    double sae;             /* Sum of Absolute Errors */
    double sse;             /* Sum of Squared Errors */
    unsigned int positives; /* Positive samples */
    unsigned int negatives; /* Negative samples */

    Scorer();
    ~Scorer();
    void add(Observation& obs, double prediction);
    void show();
    void reset();
};

#endif