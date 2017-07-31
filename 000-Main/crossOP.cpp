//
// Created by jam on 28-Jul-17.
//

#include <vector>
#include <stdexcept>
#include "crossOP.hpp"

template<typename T>
void crossOP::multiply(T *mat1, T *mat2, int &rows1, int &cols1, int &rows2,
                       int &cols2, std::vector<T> &home) {
    /// (AB)ij == Sum_k=0k=m-1[A_ij*B_jk]
    setAll(rows1, rows2, cols1, cols2);
    home.assign(rows1 * cols2, 0);
    if (rows1 == rows2 && cols1 == cols2) { multiply_tiled(mat1, mat2, home); }
    else if (cols1 != rows2) {
        throw std::invalid_argument(
                "Matrix 1 Columns do not match Matrix 2 Rows.");
    } else { ikj(mat1, mat2, home); }
}

// Naive Multiplication
template<typename T>
void crossOP::ikj(T *mat1, T *mat2, std::vector<T> &home) {
    for (int i = 0; i < _rows1; ++i) {
        for (int k = 0; k < _cols2; ++k) {
            for (int j = 0; j < _rows2; ++j) {
                home[i * _rows1 + k] +=
                        mat1[i * _cols1 + j] * mat2[j * (_cols2) + k];
            }
        }
    }
}

// Tiling Multiplication
template<typename T>
void crossOP::multiply_tiled(T *mat1, T *mat2, std::vector<T> &home) {
    long long int TILE = llround(_rows1 / 2);
    int N = (_rows1);
    /* Use tile by tile  tiles */
    /* Loop over all the tiles, stride by tile size */
    for (int i = 0; i < N; i += TILE)
        for (int j = 0; j < N; j += TILE)
            for (int k = 0; k < N; k += TILE)
                /* Regular multiply inside the tiles */
                for (int y = i; y < i + TILE; y++) // rows
                    for (int x = j; x < j + TILE; x++) // columns
                        for (int z = k; z < k + TILE; z++) { // 2nd Rows
                            home[y * _rows1 + x] +=
                                    mat1[y * _cols1 + z] *
                                    mat2[z * _cols2 + x];
                        }
}

//void crossOP::setAll(int rows1, int rows2, int cols1, int cols2) {
//    _rows1 = rows1;
//    _rows2 = rows2;
//    _cols1 = cols1;
//    _cols2 = cols2;
//}