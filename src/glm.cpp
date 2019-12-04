#include <cmath>
#include "glm.hpp"


double Gaussian::link(double mu){
    return mu;
};

double Gaussian::link_inverse(double theta){
    return theta;
};


double Binomial::link(double mu){
    return log(mu / (1 - mu));
};

double Binomial::link_inverse(double theta){
    return 1 / (1 + exp(-theta));
};


double Poisson::link(double mu){
    return log(mu);
};

double Poisson::link_inverse(double theta){
    return exp(theta);
};


/*
 * Generalized Linear Model.
 */
GLM::GLM(const RegressionType& regression_type, unsigned int bits, double lambda,
         double eta){
    this->bits = bits;
    this->eta = eta;
    this->lambda = lambda;
    this->mask = pow(2, bits) - 1;
    this->coeffs = vector<double>(pow(2, bits));
    // Set regression
    switch(regression_type){
        case LINEAR: {this->regression = new Gaussian();};
        case LOGISTIC: {this->regression = new Binomial();};
        case POISSON: {this->regression = new Poisson();};
    };
};


double GLM::fit(Observation& obs){
    double residual = predict(obs) - obs.response;
    for (Feature& feature : obs.features){
        size_t key = fhash(feature, mask);
        double grad = feature.value * residual;
        double regularizer = lambda * coeffs[key];
        coeffs[key] = coeffs[key] - eta * (grad + regularizer);
    }
    return residual;
};


double GLM::predict(Observation& obs){
    double y = 0;
    for (Feature& feature : obs.features){
        y += coeffs[fhash(feature, mask)] * feature.value;
    }
    return regression->link_inverse(y);
};


unsigned int GLM::feature_count(){
    int count = 0;
    for (size_t i = 0; i < coeffs.size(); i++){
        if (coeffs[i] > TOLERANCE) {count+= 1;};
    }
    return count;
};