//
// Created by jam on 05-Jul-17.
//

#ifndef MATRIX_TESTS_H
#define MATRIX_TESTS_H

#include <vector>
#include <iostream>
#include <iterator>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <math.h>   /* fabs */
#include "../000-Main/helper.hpp"
#include "../000-Main/matrix.hpp"

class tests {
public:
    std::vector<std::string> mErrors;
    std::vector<double> mTiming;
    std::vector<std::string> mTimingName;

    double tolerance = 0.001;
    helper valueRange;
    std::vector<double> doubleVector1 = valueRange.range(0., 10., 0.1);
    std::vector<int> intVector1 = valueRange.range(0, 100, 1);
    std::vector<int> intVectorLarge = valueRange.range(0, 1000000, 1);
    std::vector<double> doubleVectorLarge = valueRange.range(0., 9000000., 1.);

    std::vector<float> floatVector1 = valueRange.range((float) 0.,
                                                       (float) 10.0,
                                                       (float) 0.1);
    std::vector<int> additionVector = valueRange.range(0, 200, 2);

    std::vector<int> additionVectorLarge = valueRange.range(0, 1000000 * 2, 2);
    std::vector<double> additionVectorDouble = valueRange.range(0., 200., 2.);
    std::vector<double> additionVectorDoubleLarge = valueRange.range(0.,
                                                                     9000000 *
                                                                     2., 2.);
    std::vector<int> non_transposedMatrix{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
                                          12, 13, 14, 15, 16};
    std::vector<int> tranposeMatrix = {1, 5, 9, 13,
                                       2, 6, 10, 14,
                                       3, 7, 11, 15,
                                       4, 8, 12, 16};
    std::vector<int> multiplyMatrix = {90, 100, 110, 120,
                                       202, 228, 254, 280,
                                       314, 356, 398, 440,
                                       426, 484, 542, 600};
    std::vector<int> rot{5, 1, 2, 6,
                         1, 1, 9, 3,
                         1, 1, 2, 3,
                         8, 1, 2, 7};
    std::vector<int> realRot{8, 1, 1, 5,
                             1, 1, 1, 1,
                             2, 2, 9, 2,
                             7, 3, 3, 6};
    //TODO: Need a CSV reader.
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
    void matrixAdd(std::vector<T> &test_vector1, std::vector<T> &test_vector2,
                   std::vector<T> &answer_vector, std::string name);

    template<typename T>
    static std::vector<T> vectorGen(matrix<T> &array);

    template<typename T>
    void
    matrixTranpose(std::vector<T> &test_vector, std::vector<T> &transposed);

    template<typename T>
    void testAsssertion(matrix<T> expected, matrix<T> actual, std::string name,
                        double timer);

    void timing();

    template<typename T>
    void matrixSub(std::vector<T> &test_vector1, std::vector<T> &test_vector2,
                   std::string name);

    template<typename T>
    void matrixMultiply(std::vector<T> &test_vector1, int tv1Rows,
                        std::vector<T> &test_vector2, int tv2Rows,
                        std::vector<T> &expected, std::string name);

    template<typename T>
    void
    matrixRotate(std::vector<T> &test_vector1, std::vector<T> &expected,
                 int rows,
                 int columns, std::string name, int value);
};


#endif //MATRIX_TESTS_H
