#ifndef ESTIMATOR_HPP
#define ESTIMATOR_HPP

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include "reader.hpp"

#define TOLERANCE 1e-6
using namespace std;
extern hash<string> hasher;


struct Feature {
    string name;
    double value;
};


size_t fhash(Feature feature, unsigned int mask);


/*
 * Observation
 * Data structure used by the estimators to consume
 * information.
 * 
 * @param row: input row to build the observation from.
 * 
 * @return record as a vector of strings.
 */

class Observation{
public:
    double response;
    vector<Feature> features;
    Observation(string& s, bool binary);
};


/*
 * Estimator base class.
 */
class Estimator{
public:

    virtual double fit(Observation& obs){};
    virtual double predict(Observation& obs){};
    virtual unsigned int feature_count(){};
};

#endif