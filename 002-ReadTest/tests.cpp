//
// Created by jam on 05-Jul-17.
//

#include "csvReader.hpp"

int main() {
    csvReader csvr("test.csv");

    for (int i = 0; i < 9; i++) {
        std::cout << csvr.getValue(i) << std::endl;
    }
}
