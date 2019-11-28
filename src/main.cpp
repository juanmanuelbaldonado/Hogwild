#include <iostream>
#include <string>
#include <set>
#include <vector>
#include "solver.cpp"

using namespace std;

set<string> predictors = {
    // "id",
    // "click",
    "hour",
    "C1",
    "banner_pos",
    "site_id",
    "site_domain",
    "site_category",
    "app_id",
    "app_domain",
    "app_category",
    "device_id",
    "device_ip",
    "device_model",
    "device_type",
    "device_conn_type",
    "C14",
    "C15",
    "C16",
    "C17",
    "C18",
    "C19",
    "C20",
    "C21",
};

set<string> categoricals = predictors;


int main(int argc, char *argv[]){
    std::string path = "../ADMM/data/avazu/train";
    CSVReader reader(path, ',');
    string response_attr = "click";
    ModelSpec model(predictors, categoricals, response_attr);
    int sample_size = 10000000;
    double sample_rate = 0.5;
    unsigned int size = 20;
    double lambda = 0.001;
    double eta = 5e-4;
    unsigned int maxiters = 1;
    unsigned int nworkers = 1;
    cout << "Started training.." << endl;
    Estimator estimator = Hogwild(size, eta, lambda, nworkers, model, LOGISTIC,
                                  sample_rate, maxiters, reader);
}

