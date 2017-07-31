//
// Created by jam on 04-Jul-17.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H


#include <vector>
#include <iostream>
#include <map>
#include "csvReader.hpp"
#include "binaryOP.hpp"
#include "binaryOP.cpp"
//#include "crossOP.hpp"
#include "crossOP.cpp"

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
        vector = matrixVector.data();

    }

    matrix(int rows, int columns) : _rows(rows), _columns(columns) {
        matrixVector.reserve(_rows * _columns);
        vector = matrixVector.data();
    };

    ~matrix() {}

    /// Activate transpose
    void transpose(bool copy = false) {
        (transposedMatrix) ? (transposedMatrix = false)
                           : (transposedMatrix = true);
        if (copy) {
            for (auto i = 0; i < _rows; i++) {
                for (auto j = 0; j < _columns; j++) {
                    matrixVector.push_back(vector[j * (_columns) + i]);
                }
            }
            vector = matrixVector.data();
        }
        std::swap(_rows, _columns);
    }

    void pad(bool copy = false) {
        (!paddedMatrix) ? (paddedMatrix = true)
                        : (paddedMatrix = false);
        if (copy) {
            for (auto i = 0; i < _rows; i++) {
                for (auto j = 0; j < _columns; j++) {
                    matrixVector.push_back(vector[j * (_columns) + i]);
                }
            }
            vector = matrixVector.data();
        }
    };

    /// Psuedo-2D arrray from a 1D array
    T operator()(int i, int j) {
        if (transposedMatrix) std::swap(i, j);
        return (paddedMatrix) ? operation_helper(i, j, 0, 1)
                              : operation_helper(i, j, 0, 0);
    }


    /// Binary operations
    void add(matrix<T> &mat1, matrix<T> &mat2) {
        int rank1 = mat1.getRank();
        int rank2 = mat2.getRank();
        binaryOP.add(mat1.vector, mat2.vector, rank1, rank2, matrixVector);
    }

    void subtract(matrix<T> &mat1, matrix<T> &mat2) {
        int rank1 = mat1.getRank();
        int rank2 = mat2.getRank();
        binaryOP.subtract(mat1.vector, mat2.vector, rank1, rank2,
                          matrixVector);
    }
    /// Cross Operations
    void multiply(matrix<T> &mat1, matrix<T> &mat2) {
        int row1, row2, col1, col2;
        row1 = mat1.getRows();
        row2 = mat2.getRows();
        col1 = mat1.getColumns();
        col2 = mat2.getColumns();
        crossOP.multiply(mat1.vector, mat2.vector, row1, col1, row2, col2,
                         matrixVector);
    }


    /// Hold the dimensions of the matrix
    int getRows() { return _rows; }

    int getColumns() { return _columns; }

    int getRank() { return _columns * _rows; }


    /// Rotational work
    void rotate(int degree) {
        if (degree == 90) {
            rotate90pos();
            this->transpose();
        } else if (degree == -90) {
            rotate90neg();
            this->transpose();
        } else {}
    }

    void triangle_off_diagonal(std::string &kind) {
        if (_rows != _columns) {
            throw std::invalid_argument(
                    "Needs a Square Matrix");
        }
        enum lower {
            l1, l2, l3, l4
        };
        enum upper {
            u1, u2, u3, u4
        };
        std::map<std::string, lower> _lower;
        _lower["lower"] = l1;
        _lower["Lower"] = l2;
        _lower["l"] = l3;
        _lower["L"] = l4;

        std::map<std::string, upper> _upper;
        _upper["upper"] = u1;
        _upper["Upper"] = u2;
        _upper["u"] = u3;
        _upper["U"] = u4;

        for (auto it = _lower.begin(); it != _lower.end(); it++) {
            if (it->first == kind) {
                lowertriangle_off_diagonal();
                vector = matrixVector.data();
            }
        }
        for (auto it = _upper.begin(); it != _upper.end(); it++) {
            if (it->first == kind) {
                uppertriangle_off_diagonal();
                vector = matrixVector.data();
            }
        }
    }

private:
    int _columns;
    T *vector;
    bool transposedMatrix = false;
    bool paddedMatrix = false;
    binaryOP binaryOP;
    crossOP crossOP;


    /// Rotation Work
    void rotate90pos() {
        transpose(true);
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _columns / 2; ++j) {
                std::swap(matrixVector[(i * _columns) + j],
                          matrixVector[(i * _columns) + _columns - j - 1]);
            }
        }

    }

    void rotate90neg() {
        transpose(true);
        for (int i = 0; i < _rows / 2; ++i) {
            for (int j = 0; j < _columns; ++j) {
                std::swap(matrixVector[(i * _rows + j)],
                          matrixVector[j - _columns * (i - _rows + 1)]);
//                matrixVector[(_rows*_columns) -(_columns) - (_columns*i)+ j]);
            }
        }
    }

    void uppertriangle_off_diagonal() {
        matrixVector.assign(_rows * _columns, 0);
        for (int row = 0; row < _rows; ++row) {
            for (int col = _columns - 1; col > row; --col) {
                matrixVector[row * _rows + col] = vector[row * _rows + col];
            }
        }
    }

    void lowertriangle_off_diagonal() {
        matrixVector.assign(_rows * _columns, 0);
        for (int row = 1; row < _rows; ++row) {
            for (int col = 0; col < row; ++col) {
                matrixVector[row * _rows + col] = vector[row * _rows + col];
            }
        }
    }

    T operation_helper(int i, int j, bool mVector, bool mPad) const {
        /**
         * Cases:
            byteVector: Filled MatrixVector
            bytePadding: Padded Vector
         */
#define byteVector (1 << 0)
#define bytePadding (1 << 1)
        switch ((mVector ? byteVector : 0) | (mPad ? bytePadding : 0)) {
            case 0:
                return (i > _rows - 1 || j > _columns - 1 ||
                        i * _columns + j > _rows *
                                           _columns - 1)
                       ? throw std::invalid_argument(
                                "Operator Matrix () out of bonds")
                       : vector[i * (_columns) + j];

            case byteVector:
                return (i > _rows - 1 || j > _columns - 1 ||
                        i * _columns + j > _rows *
                                           _columns - 1)
                       ? throw std::invalid_argument(
                                "Operator Matrix () out of bonds")
                       : matrixVector[i * (_columns) + j];

            case bytePadding:
                return (i > _rows - 1 || j > _columns - 1 ||
                        i * _columns + j > _rows *
                                           _columns - 1)
                       ? 0
                       : vector[i * (_columns) + j];
            case byteVector + bytePadding:
                return (i > _rows - 1 || j > _columns - 1 ||
                        i * _columns + j > _rows *
                                           _columns - 1)
                       ? 0
                       : matrixVector[i * (_columns) + j];
            default:
                break;
        }
    }

protected:
    int _rows;
    std::vector<T> matrixVector;
};


#endif //MATRIX_MATRIX_H
