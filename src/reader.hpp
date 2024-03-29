#ifndef READER_HPP
#define READER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "utils.hpp"

using namespace std;

/*
 * SVMlight format parser.
 * @param inputFileName: path to input file.
 */
class Reader{
private:
    string currentLine;
    ifstream fileStream;
    string inputFileName;
    char separator;

public:
    Reader(string inputFileName);
    ~Reader();
    void next();      /* Go to next line */
    string getLine(); /* Get currrent line */
    void top();
};

#endif