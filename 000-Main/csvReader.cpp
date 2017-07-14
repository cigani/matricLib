//
// Created by jam on 07-Jul-17.
//

#include "csvReader.hpp"

template
class csvReader<int>;

template
class csvReader<float>;

template
class csvReader<double>;

template<typename T>
csvReader<T>::csvReader(std::string input) {
    filename = input;
    read();
}

template<typename T>
csvReader<T>::csvReader() {}

template<typename T>
csvReader<T>::~csvReader() {};
template<typename T>
void csvReader<T>::read() {
    rows = 0;
    columns = 0;
    std::ifstream fin(filename);
//    assert(fin.is_open());
    std::string line;
    while (std::getline(fin, line)) {                       // for each line
        std::istringstream sString(line);
        while (sString) {
            std::string compString;
            if (!getline(sString, compString, ',')) {
                break;
            }
            mCSV.push_back(std::stod(compString)); // add to the current row
        }
    }
}

template<typename T>
std::vector<T> csvReader<T>::getValues() {
    return mCSV;
}

template<typename T>
T csvReader<T>::getValue(int i) {
    return mCSV.at(i);
}

template<typename T>
void csvReader<T>::print() {
    for (auto n: mCSV) {
        std::cout << n << std::endl;
    }
}

template<typename T>
csvReader<T>::csvReader(std::string input, std::vector<T> &matrix_vector) {
    filename = input;
    read(matrix_vector);
}

template<typename T>
void csvReader<T>::read(std::vector<T> &matrix_vector) {
    rows = 0;
    columns = 0;
    std::ifstream fin(filename);
    assert(fin.is_open());
    std::string line;
    while (std::getline(fin, line)) {                       // for each line
        std::istringstream sString(line);
        while (sString) {
            std::string compString;
            if (!getline(sString, compString, ',')) {
                break;
            }
            matrix_vector.push_back(
                    std::stod(compString)); // add to the current row
        }
    }

}
