#include <cmath>
#include <iostream>

/*
 * Regression base type
 */
class Regression {
    public:
    virtual double link(double mu){};
    virtual double link_inverse(double theta){};
};


class Gaussian : public Regression {
public:
    double link(double mu){
        return mu;
    };
    double link_inverse(double theta){
        return theta;
    };
};


class Binomial : public Regression {
public:
    double link(double mu){
        return log(mu / (1 - mu));
    };
    double link_inverse(double theta){
        return 1 / (1 + exp(-theta));
    };
};


class Poisson : public Regression {
public:
    double link(double mu){
        return log(mu);
    };
    double link_inverse(double theta){
        return exp(theta);
    };
};

Gaussian LINEAR;
Binomial LOGISTIC;
Poisson POISSON;

