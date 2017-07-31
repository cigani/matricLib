//
// Created by jam on 07-Jul-17.
//

#ifndef MATRIX_CSVREADER_H
#define MATRIX_CSVREADER_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

template<typename T>
class csvReader {
private:
    /// System of <doubles> expressions.
    std::vector<T> mCSV;

    /// Filename to load our matrix from.
    std::string filename;

    /// Method to read files called in the constructor.
    void read();

    void read(std::vector<T> &matrix_vector);

    /// Number of rows present in the matrix
    int rows;

    /// Number of columns present in the matrix
    int columns;

public:
    /// \brief Constructor to generate the system of equations
    /// \param input - The file name containing equations.
    csvReader(std::string input);

    csvReader(std::string input, std::vector<T> &matrix_vector);

    ///Constructor to generate the system of equations
    csvReader();

    //! A virtual destructor for the Initial Vector class.
    virtual ~csvReader();

    /// Method to return the values contained in the vector.
    std::vector<T> getValues();

    /// Method to print out the equations
    void print();

    /// \brief Method to return an individual equation from the system matrix
    /// \param i  The index of the value to be returned.
    /// \return  Returns a Expression which contains a single equation.
    T getValue(int i);
};

#endif //MATRIX_CSVREADER_H