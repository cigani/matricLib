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


    matrix(std::vector<T> &array, int _M, int _N) : rows(_M), columns(_N),
                                                    vector(array.data()) {}
    matrix() {}
    matrix(int _M, int _N) : rows(_M), columns(_N) {
        matrixVector.reserve(_M * _N);
    };
    ~matrix() {}

    // Activate transpose
    void transpose() { transposedMatrix = true; }
    /// Psuedo-2D arrray from a 1D array
    T operator()(int i, int j) {
        if (!matrixVector.empty()) {
            return !(i < rows && j <= columns) ? throw std::invalid_argument(
                    "Operator Matrix () out of bonds") : matrixVector[
                           i * (columns) + j];
        } else if (transposedMatrix) {
            return !(i < rows && j <= columns) ? throw std::invalid_argument(
                    "Operator Matrix () out of bonds") : vector[j * (rows) +
                                                                i];
        } else {
            return !(i < rows && j <= columns) ? throw std::invalid_argument(
                    "Operator Matrix () out of bonds") : vector[i * (rows) +
                                                                j];
        }
    }

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


    void multiply(matrix<T> &mat1, matrix<T> &mat2) {
        matrixVector.assign(rows * columns, 0);
        multiply_tiled(mat1, mat2);
    }

    void multiply_tiled(matrix<T> &mat1, matrix<T> &mat2) {
        long long int TILE = llround(mat1.rows / 2);
        int N = (mat1.rows);
        /* Use tile by tile  tiles */
        /* Loop over all the tiles, stride by tile size */
        for (int i = 0; i < N; i += TILE)
            for (int j = 0; j < N; j += TILE)
                for (int k = 0; k < N; k += TILE)
                    /* Regular multiply inside the tiles */
                    for (int y = i; y < i + TILE; y++) // rows
                        for (int x = j; x < j + TILE; x++) // columns
                            for (int z = k; z < k + TILE; z++) // 2nd Rows
                                matrixVector[y * rows + x] +=
                                        mat1(y, z) * mat2(z, x);
    }
    /// Hold the dimensions of the matrix
    int getRows() { return rows; }

    int getColumns() { return columns; }

private:
    int rows;
    int columns;
    T *vector;
    std::vector<T> matrixVector;
    bool transposedMatrix = false;
};


#endif //MATRIX_MATRIX_H
