//
// Created by jam on 26-Jul-17.
//

#ifndef MATRIX_MADDITION_H
#define MATRIX_MADDITION_H

#include <vector>

class binaryOP {
public:
    binaryOP() = default;

    ~binaryOP() = default;

    template<typename T>
    void add(T *mat1, T *mat2, int &rank1, int &rank2, std::vector<T> &home);

    template<typename T>
    void
    subtract(T *mat1, T *mat2, int &rank1, int &rank2, std::vector<T> &home);
};


#endif //MATRIX_MADDITION_H
