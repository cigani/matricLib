//
// Created by jam on 05-Jul-17.
//

#include <vector>
#include <iostream>
#include <iterator>
#include "tests.h"

int main() {
    /// Tests declare
    tests tests;

    /// Misc Variables

    /// Structure tests
    tests.matrixEqual(tests.intVector1, "int vector 1");
    tests.matrixEqual(tests.doubleVector1, "double vector 1");
    tests.matrixEqual(tests.floatVector1, "float vector 1");

    /// Binary Operation tests
    tests.matrixAdd(tests.intVector1, tests.intVector1, tests.additionVector,
                    "Addition");
    tests.matrixAdd(tests.doubleVector1, tests.doubleVector1,
                    tests.additionVectorDouble, "Double addition");
    tests.matrixSub(tests.intVector1, tests.intVector1);
    tests.matrixSub(tests.doubleVector1, tests.doubleVector1);

    /// Manipulation
    tests.matrixTranpose(tests.non_transposedMatrix, tests.tranposeMatrix);

    /// Error Logging
    tests.iterateVectors(tests.mErrors);


    return 0;
}


template<typename T>
void
tests::matrixTranpose(std::vector<T> &test_vector,
                      std::vector<T> &transposed) {
    matrix<int> trans(test_vector, 4, 4);
    matrix<int> real_trans(transposed, 4, 4);
    trans.transpose();
    testAsssertion(trans, real_trans, "Transpose");


}
template<typename T>
void
tests::matrixSub(std::vector<T> &test_vector1, std::vector<T> &test_vector2) {
    matrix<T> vec1(test_vector1, 10, 10);
    matrix<T> vec2(test_vector2, 10, 10);
    matrix<T> vec3(10, 10);
    std::vector<T> answer_vector = vectorGen(vec1);
    matrix<T> vec_answer(answer_vector, 10, 10);
    vec3.subtract(vec1, vec2);
    testAsssertion(vec3, vec_answer, "Subtraction");

}
template<typename T>
void
tests::matrixAdd(std::vector<T> &test_vector1, std::vector<T> &test_vector2,
                 std::vector<T> &answer_vector, std::string name) {
    matrix<T> vec1(test_vector1, 10, 10);
    matrix<T> vec2(test_vector2, 10, 10);
    matrix<T> vec3(10, 10);
    matrix<T> vec_answer(answer_vector, 10, 10);
    vec3.add(vec1, vec2);

    testAsssertion(vec3, vec_answer, name);
//    for (auto i = 0; i < 10; i++) {
//        for (auto j = 0; j < 10; j++) {
//            std::cout << "I: " << i << "\t" << "J: " << j << "\t" <<
//                      vec_answer(i, j) << " = " << vec3(i, j) << std::endl;
//        }
//    }
}

template<typename T>
void tests::matrixEqual(std::vector<T> &theVector, std::string a_name) {
    matrix<T> new_vector(theVector, 10, 10);
    std::vector<T> test_vector;
    for (auto i = 0; i < 10; i++) {
        for (auto j = 0; j < 10; j++) {
//            std::cout << "I: " << i << "\t" << "J: " << j << "\t" <<
//                      new_vector(i, j) << std::endl;
            test_vector.push_back(new_vector(i, j));
        }
    }
    testAsssertion(theVector, test_vector, a_name);
}

template<typename T>
void tests::testAsssertion(std::vector<T> expected,
                           std::vector<T> actual,
                           std::string name) {
    for (unsigned long i = 0; i < actual.size(); i++) {
        double evaluate = expected.at(i) - actual.at(i);
        if (fabs(evaluate) > tolerance) {
            testErrorCode(name);
            break;
//            std::cout << "Expected: " << expected[i] << " | "
//                      << "Actual: " << actual[i] << "\n";
        }
    }
};

template<typename T>
void tests::testAsssertion(matrix<T> expected,
                           matrix<T> actual,
                           std::string name) {

    for (int i = 0; i < actual.columns; i++) {
        for (int j = 0; j < actual.rows; j++) {
            auto evaluate = expected(i, j) - actual(i, j);
            if (fabs(evaluate > tolerance)) {
                testErrorCode(name);
                break;
            }
        }
    }
}


void tests::iterateVectors(std::vector<std::string> &returns) {
    std::cout
            << "--------------------------------------------------------------"
            << "\n";
    if (returns.size() == 0) { std::cout << "No Errors"; }
    else { for (auto n: returns) { std::cout << "Error: " << n << "\n"; }}
    std::cout << std::endl;

};

void tests::testErrorCode(std::string &ErrorType) {
    mErrors.push_back(ErrorType);
}

template<typename T>
std::vector<T> tests::vectorGen(matrix<T> &array) {
    int dims = (array.columns * array.rows);
    std::vector<T> vector(dims);
    return vector;
}