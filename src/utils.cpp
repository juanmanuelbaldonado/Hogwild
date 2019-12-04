#include "utils.hpp"

Vector& operator+=(Vector &x, const Vector &y) {
    for (size_t i = 0; i < x.size(); i++) x[i] += y[i];
    return x;
};


Vector& operator-=(Vector &x, const Vector &y) {
    for (size_t i = 0; i < x.size(); i++) x[i] -= y[i];
    return x;
};


Vector operator+(Vector x, const Vector &y) {
    Vector res = x;
    res += y;
    return res;
};


Vector operator-(Vector x, const Vector &y) {
    Vector res = x;
    res -= y;
    return res;
};


void divide(Vector& v, unsigned int n){
    for (size_t i = 0; i < v.size(); i++) v[i] /= n;
};


void print_vector(vector<string> v){
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) cout << v[i] << " ";
    cout << "]" << endl;
};


/*
 * Splits a string into substrings at the positions
 * that match the separator.
 * 
 * @param str: input string to be parsed.
 * @param separator: separating char.
 * 
 * @return a vector containing the substrings.
 */
vector<string> split(string str, char separator){
    replace(str.begin(), str.end(), separator, ' ');
    vector<string> res;
    stringstream ss(str);
    string temp;
    while (ss >> temp)
        res.push_back(temp);
    return res;
};