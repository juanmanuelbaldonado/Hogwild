#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "utils.cpp"

using namespace std;


/*
 * Splits a string into substrings at the 
 * 
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


struct Feature {
    string name;
    string value;
};


struct Row {
    string target;
    vector<Feature> features;
};


Row str_to_row(string raw){
    vector<string> registers = split(raw, ' ');
    Row row;
    row.target = registers[0];
    for (size_t i = 1; i < registers.size(); i++){
        Feature feature;
        string s = registers[i];
        feature.name = s.substr(0, s.find(':'));
        feature.value = s.substr(s.find(':'), s.size());
        row.features.push_back(feature);
    };
    return row;
};

/*
 * Parser for SVMlight format
 * @param inputFileName: input file name (full path).
 */
class Reader{
private:
    // string currentLine;
    Row currentRow;
    ifstream fileStream;
    string inputFileName;
    char separator;

public:
    Reader(string inputFileName);
    ~Reader();
    void next(); /* Go to next line */
    Row get();   /* Get currrent line */
    bool end();
    void restart();
};

Reader::Reader(string inputFileName){
    this->inputFileName = inputFileName;
    fileStream.open(inputFileName);
    next(); // Load first line.
}

Reader::~Reader(){
    fileStream.close();
};

void Reader::next(){
    string current_line;
    getline(fileStream, current_line);
    currentRow = str_to_row(current_line);
}

Row Reader::get(){
    return currentRow;
}

bool Reader::end(){
    return fileStream.eof();
}

void Reader::restart(){
    fileStream.clear();
    fileStream.seekg(0);
    next();
}