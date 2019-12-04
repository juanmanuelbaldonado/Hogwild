#include "estimator.hpp"

hash<string> hasher;

size_t fhash(Feature feature, unsigned int mask){
    return hasher(feature.name) & mask;
}


Observation::Observation(string& s, bool binary=true){
    vector<string> registers = split(s, ' ');
    response = stod(registers[0]);
    if (binary) {response = response > 0 ? 1 : 0;};
    for (size_t i = 1; i < registers.size(); i++){
        Feature feature;
        string s = registers[i];
        feature.name = s.substr(0, s.find(':'));
        feature.value = stod(s.substr(s.find(':') + 1, s.size()));
        features.push_back(feature);
    };
}