//
// Created by jam on 04-Jul-17.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H


#include <vector>
#include <iostream>


template<typename T>
class matrix {
public:
    T *vector;
    std::vector<T> matrixVector;
    matrix(std::vector<T> &array, int _M, int _N) : rows(_M), columns(_N),
                                                    vector(array.data()) {}
    matrix() {}
    matrix(int _M, int _N) : rows(_M), columns(_N) {
        matrixVector.reserve(_M * _N);
    };
    ~matrix() {}

    /// Psuedo-2D arrray from a 1D array
    T operator()(int i, int j) {
        if (!matrixVector.empty()) {
            return !(i < rows && j <= columns) ? throw std::invalid_argument(
                    "Operator Matrix () out of bonds") : matrixVector[
                           i * (columns) + j];
        } else {
            return !(i < rows && j <= columns) ? throw std::invalid_argument(
                    "Operator Matrix () out of bonds") : vector[i * (columns) +
                                                                j];
        }
    }

    void append(T value) { matrixVector.push_back(value); }

    void add(matrix<T> &mat1, matrix<T> &mat2) {
        for (int i = 0; i < mat1.columns; i++) {
            for (int j = 0; j < mat1.rows; j++) {
                matrixVector.push_back(mat1(i, j) + mat2(i, j));

            }
        }
    };

    void subtract(matrix<T> &mat1, matrix<T> &mat2) {
        for (int i = 0; i < mat1.columns; i++) {
            for (int j = 0; j < mat1.rows; j++) {
                matrixVector.push_back(mat1(i, j) - mat2(i, j));

            }
        }
    }

    int rows;
    int columns;
private:
    /// Hold the dimensions of the matrix

};


#endif //MATRIX_MATRIX_H
