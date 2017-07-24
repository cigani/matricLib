//
// Created by jam on 04-Jul-17.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H


#include <vector>
#include <iostream>
#include <map>
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
        (!transposedMatrix) ? (transposedMatrix = true)
                            : (transposedMatrix = false);
        if (copy) {
            for (auto i = 0; i < _rows; i++) {
                for (auto j = 0; j < _columns; j++) {
                    matrixVector.push_back(vector[j * (_columns) + i]);
                }
            }
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
        }
    };

    /// Psuedo-2D arrray from a 1D array
    T operator()(int i, int j) {
        if (!matrixVector.empty()) {
            return operation_helper(i, j);
        } else if (transposedMatrix) {
            return operation_helper(j, i);
        } else {
            return operation_helper(i, j);
        }
    }


    /// Binary operations
    void add(matrix<T> &mat1, matrix<T> &mat2) {
        int n, m;
        n = std::max(mat1._rows, mat2._rows);
        m = std::max(mat1._columns, mat2._columns);
        if (mat1._rows * mat1._columns != mat2._rows * mat2._rows) {
            mat1.pad();
            mat2.pad();
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                matrixVector.push_back(mat1(i, j) + mat2(i, j));
            }
        }
    }

    void subtract(matrix<T> &mat1, matrix<T> &mat2) {
        int n, m;
        n = std::max(mat1._rows, mat2._rows);
        m = std::max(mat1._columns, mat2._columns);
        if (mat1._rows * mat1._columns != mat2._rows * mat2._rows) {
            mat1.pad();
            mat2.pad();
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                matrixVector.push_back(mat1(i, j) - mat2(i, j));
            }
        }
    }

    /// Cross Operations
    void multiply(matrix<T> &mat1, matrix<T> &mat2) {
        matrixVector.assign(_rows * _columns, 0);
        if (mat1.getRows() == mat2.getRows() &&
            mat1.getColumns() == mat2.getColumns()) {
            multiply_tiled(mat1, mat2);
        } else if (mat1.getColumns() != mat2.getRows()) {
            throw std::invalid_argument(
                    "Matrix 1 Columns do not match Matrix 2 Rows.");
        } else { ikj(mat1, mat2); }
    }

    /// Hold the dimensions of the matrix
    int getRows() { return _rows; }

    int getColumns() { return _columns; }


    /// Rotational work

    void rotate(int degree) {
        if (degree == 90) {
            rotate90pos();
        } else if (degree == -90) {
            rotate90neg();
        } else {}

//            case 180: rotate180pos(this, _rows, _columns);
//            case -180: rotate180neg(this, _rows, _columns);
    }

    void triangle_off_diagonal(std::string kind) {
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
                lowertriangle_off_diagonal(this);
            }
        }
        for (auto it = _upper.begin(); it != _upper.end(); it++) {
            if (it->first == kind) {
                uppertriangle_off_diagonal(this);
            }
        }
    }
//        if (kind == "lower" || "Lower" || "l" || "L") {
//            lowertriangle_off_diagonal(this);
//        }
//        if (kind == "upper" || "Upper" || "u" || "U") {
//            uppertriangle_off_diagonal(this);
//
//        }

private:
    int _rows;
    int _columns;
    T *vector;
    std::vector<T> matrixVector;
    bool transposedMatrix = false;
    bool paddedMatrix = false;

    // Naive Multiplication
    void ikj(matrix<T> &mat1, matrix<T> &mat2) {
        for (int i = 0; i < mat1.getRows(); ++i) {
            for (int k = 0; k < mat2.getColumns(); ++k) {
                for (int j = 0; j < mat2.getRows(); ++j) {
                    matrixVector[i * _rows + k] += mat1(i, j) * mat2(j, k);
                }
            }
        }
    }

    // Tiling Multiplication
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
                            for (int z = k; z < k + TILE; z++) { // 2nd Rows
                                matrixVector[y * _rows + x] +=
                                        mat1(y, z) * mat2(z, x);
                            }
    }

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

    void uppertriangle_off_diagonal(matrix<T> *matrix1) {
        matrixVector.assign(_rows * _columns, 0);
        for (int row = 0; row < _rows; ++row) {
            for (int col = _columns - 1; col > row; --col) {
                matrixVector[row * _rows + col] = vector[row * _rows + col];
            }
        }
    }

    void lowertriangle_off_diagonal(matrix<T> *matrix1) {
        matrixVector.assign(_rows * _columns, 0);
        for (int row = 1; row < _rows; ++row) {
            for (int col = 0; col < row; ++col) {
                matrixVector[row * _rows + col] = vector[row * _rows + col];
            }
        }
    }

    T operation_helper(int i, int j) const {
        if (!matrixVector.empty()) {
            if (paddedMatrix) {
                return (i > _rows - 1 || j > _columns - 1 ||
                        i * _columns + j > _rows *
                                           _columns - 1)
                       ? 0
                       : matrixVector[i * (_columns) + j];
            } else {
                return (i > _rows - 1 || j > _columns - 1 ||
                        i * _columns + j > _rows *
                                           _columns - 1)
                       ? throw std::invalid_argument(
                                "Operator Matrix () out of bonds")
                       : matrixVector[i * (_columns) + j];
            }
        } else {
            if (paddedMatrix) {
                return (i > _rows - 1 || j > _columns - 1 ||
                        i * _columns + j > _rows *
                                           _columns - 1)
                       ? 0
                       : vector[i * (_columns) + j];
            } else {
                return (i > _rows - 1 || j > _columns - 1 ||
                        i * _columns + j > _rows *
                                           _columns - 1)
                       ? throw std::invalid_argument(
                                "Operator Matrix () out of bonds")
                       : vector[i * (_columns) + j];
            }
        }
    }


};


#endif //MATRIX_MATRIX_H
