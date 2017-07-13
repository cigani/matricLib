//
// Created by jam on 04-Jul-17.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H


#include <vector>
#include <iostream>
#include "csvReader.hpp"

template<typename T>
class matrix {
public:


    matrix(std::vector<T> &array, int rows, int columns) : _rows(rows),
                                                           _columns(columns),
                                                           vector(array.data()) {}

    matrix() {}

    matrix(std::string FILE, int rows, int columns) : _rows(rows),
                                                      _columns(columns) {
        matrixVector.reserve(_rows * _columns);
        csvReader<T> csvReader2(FILE, matrixVector);

    }

    matrix(int rows, int columns) : _rows(rows), _columns(columns) {
        matrixVector.reserve(_rows * _columns);
    };

    ~matrix() {}

    // Activate transpose
    void transpose(bool copy = false) {
        transposedMatrix = true;
        if (copy) {
            for (auto i = 0; i < _rows; i++) {
                for (auto j = 0; j < _columns; j++) {
                    matrixVector.push_back(vector[j * (_columns) + i]);
                }
            }
        }
    }

    /// Psuedo-2D arrray from a 1D array
    T operator()(int i, int j) {
        if (!matrixVector.empty()) {
            return !(i < _rows && j <= _columns)
                   ? throw std::invalid_argument(
                            "Operator Matrix () out of bonds")
                   : matrixVector[i * (_columns) + j];
        } else if (transposedMatrix) {
            return !(i < _rows && j <= _columns)
                   ? throw std::invalid_argument(
                            "Operator Matrix () out of bonds")
                   : vector[j * (_columns) + i];
        } else {
            return !(i < _rows && j <= _columns)
                   ? throw std::invalid_argument(
                            "Operator Matrix () out of bonds")
                   : vector[i * (_columns) + j];
        }
    }

    /// Binary operations
    void add(matrix<T> &mat1, matrix<T> &mat2) {
        for (int i = 0; i < mat1._columns; i++) {
            for (int j = 0; j < mat1._rows; j++) {
                matrixVector.push_back(mat1(i, j) + mat2(i, j));

            }
        }
    };

    void subtract(matrix<T> &mat1, matrix<T> &mat2) {
        for (int i = 0; i < mat1._columns; i++) {
            for (int j = 0; j < mat1._rows; j++) {
                matrixVector.push_back(mat1(i, j) - mat2(i, j));

            }
        }
    }


    /// Cross Operations
    void multiply(matrix<T> &mat1, matrix<T> &mat2) {
        matrixVector.assign(_rows * _columns, 0);
        multiply_tiled(mat1, mat2);
    }

    void multiply_tiled(matrix<T> &mat1, matrix<T> &mat2) {
        long long int TILE = llround(mat1._rows / 2);
        int N = (mat1._rows);
        /* Use tile by tile  tiles */
        /* Loop over all the tiles, stride by tile size */
        for (int i = 0; i < N; i += TILE)
            for (int j = 0; j < N; j += TILE)
                for (int k = 0; k < N; k += TILE)
                    /* Regular multiply inside the tiles */
                    for (int y = i; y < i + TILE; y++) // rows
                        for (int x = j; x < j + TILE; x++) // columns
                            for (int z = k;
                                 z < k + TILE; z++) // 2nd Rows
                                matrixVector[y * _rows + x] +=
                                        mat1(y, z) * mat2(z, x);
    }

    /// Hold the dimensions of the matrix
    int getRows() { return _rows; }

    int getColumns() { return _columns; }


    /// Rotational work

    void rotate(int degree) {
        switch (degree) {
            case 90: {
                rotate90pos();
            }
            default: {
                break;
            }
//            case -90: rotate90neg(this, _rows, _columns);
//            case 180: rotate180pos(this, _rows, _columns);
//            case -180: rotate180neg(this, _rows, _columns);
        }
    }

private:
    int _rows;
    int _columns;
    T *vector;
    std::vector<T> matrixVector;
    bool transposedMatrix = false;
    bool _copy = false;

    /// Rotation Work
    void rotate90pos() {
        transpose(true);
        for (int i = 0; i < _rows; ++i)
            for (int j = 0; j < _columns / 2; ++j)
                std::swap(matrixVector[(i * _columns) + j],
                          matrixVector[(i * _columns) + _columns - j - 1]);


    }

};


#endif //MATRIX_MATRIX_H
