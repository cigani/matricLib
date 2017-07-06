//
// Created by jam on 05-Jul-17.
//

#ifndef MATRIX_TESTS_H
#define MATRIX_TESTS_H


#include "helper.h"
#include "matrix.h"

class tests {
public:
    std::vector<std::string> mErrors;
    double tolerance = 0.001;
    helper valueRange;
    std::vector<double> doubleVector1 = valueRange.range(0., 10., 0.1);
    std::vector<int> intVector1 = valueRange.range(0, 100, 1);
    std::vector<float> floatVector1 = valueRange.range((float) 0.,
                                                       (float) 10.0,
                                                       (float) 0.1);
    std::vector<int> additionVector = valueRange.range(0, 200, 2);


    template<typename T>
    void testAsssertion(std::vector<T> expected, std::vector<T> actual,
                        std::string name);

    void iterateVectors(std::vector<std::string> &returns);

    void testErrorCode(std::string &ErrorType);
//    std::vector<double> doubleVector1, doubleVector2, doubleVector3, doubleVector4;
//    std::vector<int> intVector1, intVector2, intVector3, intVector4;
//    std::vector<float> floatVector1, floatVector2, floatVector3, floatVector4;

    template<typename T>
    void matrixEqual(std::vector<T> &theVector, std::string a_name);

    template<typename T>
    void matrixMath(std::vector<T> &test_vector1, std::vector<T> &test_vector2,
                    std::vector<T> &answer_vector, std::string name);

    template<typename T>
    void
    testAsssertion(matrix<T> expected, matrix<T> actual, std::string name);

    template<typename T>
    std::vector<T> vectorGen(matrix<T> &array);
};


#endif //MATRIX_TESTS_H
