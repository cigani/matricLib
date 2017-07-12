//
// Created by jam on 05-Jul-17.
//

#include "../000-Main/csvReader.hpp"

int main() {
    csvReader<int> csvr("test.csv");
    csvReader<float> csvReader1("test.csv");
    csvReader<double> csvReader2("test.csv");
    csvr.print();
}
