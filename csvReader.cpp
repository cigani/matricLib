//
// Created by jam on 07-Jul-17.
//

#include "csvReader.h"
#include <cassert>
#include <sstream>

csvReader::csvReader(std::string input) {
    filename = input;
    read();
}

csvReader::csvReader() {}

csvReader::~csvReader() {};

void csvReader::read() {
    rows = 0;
    columns = 0;
    std::ifstream fin(filename);
    assert(fin.is_open());
    std::string line;
    while (std::getline(fin, line)) {                       // for each line
        mCSV.push_back(std::stod(line));          // add to the current row
    }
}

std::vector<double> csvReader::getValues() {
    return mCSV;
}

double csvReader::getValue(int i) {
    return mCSV.at(i);
}

void csvReader::print() {
    std::vector<double>::iterator row;

    for (row = mCSV.begin(); row != mCSV.end(); ++row) {
        std::cout << (*row) << std::endl;
    };
}