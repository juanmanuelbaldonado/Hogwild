#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

/*
 * Parses a row of a CSV file.
 * @param str: input string to be parsed.
 * @param separator: attribute separating char.
 * 
 * @return record as a vector of strings.
 */
vector<string> split(string str, char separator){
    replace(str.begin(), str.end(), separator, ' ');
    vector<string> res;
    stringstream ss(str);
    string temp;
    while (ss >> temp)
        res.push_back(temp);
    return res;
}

struct Row{
    vector<string> attributes;
    vector<string> values;
    Row(vector<string> attrs, vector<string> vals)
        : attributes(attrs), values(vals) {};
};


/*
 * CSV reader object.
 * @param inputFileName: input file name (full path).
 * @param separator: char to be used as separator.
 */
class CSVReader{
private:
    vector<string> colNames;
    string currentLine;
    ifstream fileStream;
    string inputFileName;
    char separator;

public:
    CSVReader(string inputFileName, char separator=',');
    ~CSVReader();
    void next(); /* Go to next line */
    Row get();   /* Get currrent line */
    bool end();
    void restart();
};

CSVReader::CSVReader(string inputFileName, char separator){
    this->inputFileName = inputFileName;
    this->separator = separator;
    fileStream.open(inputFileName);
    // Load first line.
    next();
    colNames = split(currentLine, separator);
    next();
}

CSVReader::~CSVReader(){
    fileStream.close();
};

void CSVReader::next(){
    getline(fileStream, currentLine);
}

Row CSVReader::get(){
    return Row(colNames, split(currentLine, separator));
}

bool CSVReader::end(){
    return fileStream.eof();
}

void CSVReader::restart(){
    fileStream.clear();
    fileStream.seekg(0);
    next();next();
}