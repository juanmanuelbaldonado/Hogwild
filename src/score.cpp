#include "score.hpp"


Scorer::Scorer(){
    this->reset();
};

Scorer::~Scorer(){
    this->reset();
};

void Scorer::add(Observation& obs, double prediction){
    n++;
    sae += abs(prediction - obs.response);
    sse += pow(prediction - obs.response, 2);
    if (obs.response == 1) positives++;
    else negatives++;
};

void Scorer::show(){
    cout << "N: " << n << " | "
         << "MAE: " << sae / n << " | "
         << "MSE: " << sse / n << " | "
         << "positives: " << ((double) positives) / n << " | "
         << "negatives: " << ((double) negatives) / n << endl;
};

void Scorer::reset(){
    n = 0; sae = 0; sse = 0; positives = 0; negatives = 0;
};