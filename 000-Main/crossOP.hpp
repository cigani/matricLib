//
// Created by jam on 28-Jul-17.
//

#ifndef MATRIX_CROSSOP_HPP
#define MATRIX_CROSSOP_HPP


#include <cmath>

class crossOP {

public:
    template<typename T>
    void
    multiply(T *mat1, T *mat2, int &rows1, int &cols1, int &rows2, int &cols2,
             std::vector<T> &home);

private:
    int _rows1;
    int _rows2;
    int _cols1;
    int _cols2;

    void setAll(int rows1, int rows2, int cols1, int cols2) {
        _rows1 = rows1;
        _rows2 = rows2;
        _cols1 = cols1;
        _cols2 = cols2;
    };

    template<typename T>
    void multiply_tiled(T *mat1, T *mat2, std::vector<T> &home);

    template<typename T>
    void ikj(T *mat1, T *mat2, std::vector<T> &home);
};


#endif //MATRIX_CROSSOP_HPP
