//
// Created by jam on 27-Jul-17.
//

#ifndef MATRIX_IMTEST_H
#define MATRIX_IMTEST_H

#include "matrix.hpp"

class imTest {
public:
    ~imTest() = default;

public:
    imTest() = default;

    int i = 0;

    template<class T>
    void var(matrix<T> *some);
};


#endif //MATRIX_IMTEST_H
