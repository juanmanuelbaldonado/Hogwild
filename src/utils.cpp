#include "utils.hpp"

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