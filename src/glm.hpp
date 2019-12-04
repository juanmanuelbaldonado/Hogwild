#ifndef GLM_HPP
#define GLM_HPP

#include <cmath>
#include "estimator.hpp"


/*
 * Regression base type
 */
class Regression {
    public:
    virtual double link(double mu) = 0;
    virtual double link_inverse(double theta) = 0;
};


class Gaussian : public Regression {
public:
    double link(double mu);
    double link_inverse(double theta);
};


class Binomial : public Regression {
public:
    double link(double mu);
    double link_inverse(double theta);
};


class Poisson : public Regression {
public:
    double link(double mu);
    double link_inverse(double theta);
};


enum RegressionType{LINEAR, LOGISTIC, POISSON};

/*
 * Generalized Linear Model
 * 
 * @param str: input string to be parsed.
 * @param separator: attribute separating char.
 * 
 * @return record as a vector of strings.
 */
class GLM : public Estimator{
private:
    int bits;
    double lambda, eta;
    vector<double> coeffs;
    Regression* regression;
    unsigned int mask;

public:
    GLM(const RegressionType& regression_type, unsigned int bits=16,
        double lambda=0.5, double eta=1e-4);
    double fit(Observation& obs);
    double predict(Observation& obs);
    unsigned int feature_count();
};

#endif