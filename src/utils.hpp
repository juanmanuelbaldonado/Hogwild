#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

/*
 * Splits a string into substrings at the positions
 * that match the separator.
 * 
 * @param str: input string to be parsed.
 * @param separator: separating char.
 * 
 * @return a vector containing the substrings.
 */
vector<string> split(string str, char separator);

#endif