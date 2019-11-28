#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include "reader.cpp"
#include "regression.cpp"

#define TOLERANCE 1e-6

using namespace std;

hash<string> hasher;


double soft_threshold(double x, double thr){
    if (abs(x) <= thr) return 0;
    if (x > thr) return x - thr;
    if (x < - thr) return x + thr;
}


class ModelSpec{
private:
    set<string> predictors;
    set<string> categoricals;
    string response;

public:
    ModelSpec(set<string> predictors, set<string> categoricals, string response):
        predictors(predictors), categoricals(categoricals), response(response) {};

    bool is_predictor(string& s){
        return predictors.find(s) != predictors.end();
    };
    bool is_categorical(string& s){
        return categoricals.find(s) != categoricals.end();
    };
    bool is_response(string& s){
        return s == response;
    };
};


/*
 * Attribute
 * Data structure to represent attributes. If the
 * feature value is not categorical, then the value
 * attribute should be casted into float/double.
 * 
 * @param name.
 * @param value.
 * @param categorical : flag to indicate if the attribute
 *                      is a categorical feature.
 * 
 * @return attribute.
 */

class Attribute{
private:
    string name;
    string val;
    bool categorical;

public:
    Attribute(){};
    Attribute(string name, string value, bool categorical) :
        name(name), val(value), categorical(categorical) {};

    size_t key();
    double value();
};

size_t Attribute::key(){
    string key = categorical ? (name + "__" + val) : name;
    return hasher(key);
};

double Attribute::value(){
    if (categorical) return 1;
    return stod(val);
}


/*
 * Observation
 * Data structure used by the estimators to consume
 * information.
 * 
 * @param row: input row to build the observation from.
 * @param row: input row to build the observation from.
 * @param response: name of the response attribute
 * 
 * @return record as a vector of strings.
 */

class Observation{
public:
    vector<Attribute> attributes;
    Attribute response;

    Observation(Row& row, ModelSpec& model);
    void show();
};

Observation::Observation(Row& row, ModelSpec& model){
    for (size_t i = 0; i < row.attributes.size(); i++){
        Attribute attr(row.attributes[i], row.values[i],
                       model.is_categorical(row.attributes[i]));
        if (model.is_predictor(row.attributes[i])) attributes.push_back(attr);
        if (model.is_response(row.attributes[i])) this->response = attr;
    }
}

void Observation::show(){
    for(auto attr : attributes){
        cout << "key: " << attr.key() << " | "
             << "value: " << attr.value() << endl;
    };
    cout << "response: " << response.value() << endl;
};


/*
 * Estimator class
 * Use the hashing trick
 * 
 * @param str: input string to be parsed.
 * @param separator: attribute separating char.
 * 
 * @return record as a vector of strings.
 */
class Estimator{
private:
    int size;
    double lambda, eta;
    vector<atomic<double>> coeffs;
    Regression* regression;
    unsigned int mask;
    unsigned int t;

public:
    Estimator(Regression& regression, unsigned int size=16, double lambda=0.5,
              double eta=1e-4);
    double fit(Observation& obs);
    double predict(Observation& obs);
    size_t get_coefficient(int key);
    double coeff(int key);
    unsigned int feature_count();
};

Estimator::Estimator(Regression& regression, unsigned int size, double lambda,
                     double eta){
    this->size = size;
    this->eta = eta;
    this->regression = &regression;
    this->lambda = lambda;
    coeffs = vector<atomic<double>>(pow(2, size));
    this->mask = pow(2, size) - 1;
    t = 1;
}

double Estimator::fit(Observation& obs){
    double residual = predict(obs) - obs.response.value();
    for(Attribute& attr: obs.attributes){
        size_t key = get_coefficient(attr.key());
        double grad = attr.value() * residual;
        for (double g = coeffs[key]; 
             !coeffs[key].compare_exchange_strong(g, g - (eta / sqrt(t)) * grad););
        // coeffs[key] = coeffs[key] - (eta / sqrt(t))  * grad;
    }
    t++;
    return residual;
};

double Estimator::predict(Observation& obs){
    double y = 0;
    for(Attribute& attr: obs.attributes){
        y += coeffs[get_coefficient(attr.key())] * attr.value();
    }
    return regression->link_inverse(y);
};

unsigned int Estimator::feature_count(){
    int count = 0;
    for (size_t i = 0; i < coeffs.size(); i++){
        if (coeffs[i] > TOLERANCE) {count+= 1;};
    }
    return count;
}


size_t Estimator::get_coefficient(int key){
    return (key & mask);
};


double Estimator::coeff(int key){
    double val = coeffs[key];
    if (abs(val) <= lambda) return 0;
    return val;
};