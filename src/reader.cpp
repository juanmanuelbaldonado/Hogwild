#include "reader.hpp"
#include "utils.hpp"

using namespace std;

Reader::Reader(string inputFileName){
    this->inputFileName = inputFileName;
    fileStream.open(inputFileName);
    next(); // Load first line.
}

Reader::~Reader(){
    fileStream.close();
};

void Reader::next(){
    getline(fileStream, currentLine);
    if (fileStream.eof()) throw out_of_range("No more rows");
};

string Reader::getLine(){
    return currentLine;
};

void Reader::top(){
    fileStream.clear();
    fileStream.seekg(0);
    next();
};