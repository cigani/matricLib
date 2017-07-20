//
// Created by jam on 05-Jul-17.
//

#include "tests.hpp"
#include "../000-Main/csvReader.hpp"

int main() {
    /// Tests declare
    tests tests;
    // Misc Variables

    // Structure tests
    tests.matrixEqual(tests.intVector1, "int vector 1");
    tests.matrixEqual(tests.doubleVector1, "double vector 1");
    tests.matrixEqual(tests.floatVector1, "float vector 1");

    /// Binary Operation tests
    tests.matrixAdd(tests.intVector1, tests.intVector1, tests.additionVector,
                    "Addition");
    tests.matrixAdd(tests.doubleVector1, tests.doubleVector1,
                    tests.additionVectorDouble, "Double addition");
    tests.matrixAdd(tests.intVectorLarge, tests.intVectorLarge,
                    tests.additionVectorLarge, "Large Int Addition");
    tests.matrixAdd(tests.doubleVectorLarge, tests.doubleVectorLarge,
                    tests.additionVectorDoubleLarge, "Large double addition");
    tests.matrixSub(tests.intVector1, tests.intVector1, "Integer Subtraction");
    tests.matrixSub(tests.doubleVector1, tests.doubleVector1,
                    "Double Subtraction");
    tests.matrixSub(tests.additionVectorDoubleLarge,
                    tests.additionVectorDoubleLarge,
                    "Large double subtraction");

    /// Manipulation
    tests.matrixTranpose(tests.non_transposedMatrix, tests.tranposeMatrix);

    /// Non-Binary Ops
    tests.matrixMultiply(tests.non_transposedMatrix, 4,
                         tests.non_transposedMatrix, 4, tests.multiplyMatrix,
                         "Integer Multiplication");

    /// Transforms

    tests.matrixRotate(tests.rot, tests.realRot90pos, 4, 4, "90+ Rotation",
                       90);
    tests.matrixRotate(tests.rot, tests.realRot90neg, 4, 4, "90- Rotation",
                       -90);

    /// Diagonalization
    tests.matrixOffDiagonal(tests.lower_off1_input, tests.lower_off1, 4,
                            "lower",
                            "Lower");

    /// Error Logging
    tests.iterateVectors(tests.mErrors);

    // Timing
    tests.timing();
    return 0;
}

template<typename T>
void tests::matrixOffDiagonal(std::vector<T> &test_vector1,
                              std::vector<T> &expected, int rows,
                              std::string kind, std::string name) {
    clock_t tStart = clock();
    matrix<int> actual(test_vector1, rows, rows);
    matrix<int> holder(expected, rows, rows);
    actual.triangle_off_diagonal(kind);
    double timer = (double) (clock() - tStart) / CLOCKS_PER_SEC;
    matrixEqual(actual, expected, rows, rows, name);
    testAsssertion(actual, holder, name, timer);
}
template<typename T>
void
tests::matrixRotate(std::vector<T> &test_vector1, std::vector<T> &expected,
                    int rows, int columns, std::string name, int value) {
    clock_t tStart = clock();
    matrix<int> actual(test_vector1, rows, columns);
    matrix<int> holder(expected, rows, columns);
    actual.rotate(value);
    double timer = (double) (clock() - tStart) / CLOCKS_PER_SEC;
    testAsssertion(actual, holder, name, timer);
//    for (auto i = 0; i < 4; i++) {
//        std::cout<<std::endl;
//        for (auto j = 0; j < 4; j++) {
////            std::cout << "I: " << i << "\t" << "J: " << j << "\t" <<
//                     std::cout << actual(i, j) << " = " << holder(i, j) << "\t";
//        }
//    }
}

template<typename T>
void
tests::matrixMultiply(std::vector<T> &test_vector1,
                      int tv1Rows,
                      std::vector<T> &test_vector2,
                      int tv2Rows,
                      std::vector<T> &expected,
                      std::string name) {
    int col1 = test_vector1.size() / tv1Rows;
    int col2 = test_vector2.size() / tv2Rows;
    clock_t tStart = clock();
    matrix<T> matrix1(test_vector1, tv1Rows, col1);
    matrix<T> matrix2(test_vector2, tv2Rows, col2);
    matrix<T> holder(tv1Rows, col2);
    matrix<T> actual(expected, tv1Rows, col2);
    holder.multiply(matrix1, matrix2);
    double timer = (double) (clock() - tStart) / CLOCKS_PER_SEC;
    testAsssertion(actual, holder, name, timer);
}
template<typename T>
void
tests::matrixTranpose(std::vector<T> &test_vector,
                      std::vector<T> &transposed) {
    clock_t tStart = clock();
    matrix<int> trans(test_vector, 4, 4);
    matrix<int> real_trans(transposed, 4, 4);
    trans.transpose();
    double timer = (double) (clock() - tStart) / CLOCKS_PER_SEC;
    testAsssertion(trans, real_trans, "Transpose", timer);


}

template<typename T>
void
tests::matrixSub(std::vector<T> &test_vector1, std::vector<T> &test_vector2,
                 std::string name) {
    clock_t tStart = clock();
    int dim = (int) sqrt(test_vector1.size());
    matrix<T> vec1(test_vector1, dim, dim);
    matrix<T> vec2(test_vector2, dim, dim);
    matrix<T> vec3(dim, dim);
    std::vector<T> answer_vector = vectorGen(vec1);
    matrix<T> vec_answer(answer_vector, dim, dim);
    vec3.subtract(vec1, vec2);
    double timer = (double) (clock() - tStart) / CLOCKS_PER_SEC;
    testAsssertion(vec3, vec_answer, name, timer);

}

template<typename T>
void
tests::matrixAdd(std::vector<T> &test_vector1, std::vector<T> &test_vector2,
                 std::vector<T> &answer_vector, std::string name) {
    int dim = (int) sqrt(test_vector1.size());
    clock_t tStart = clock();
    matrix<T> vec1(test_vector1, dim, dim);
    matrix<T> vec2(test_vector2, dim, dim);
    matrix<T> vec3(dim, dim);
    matrix<T> vec_answer(answer_vector, dim, dim);
    vec3.add(vec1, vec2);
    double timer = (double) (clock() - tStart) / CLOCKS_PER_SEC;
    testAsssertion(vec3, vec_answer, name, timer);
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
void
tests::matrixEqual(matrix<T> &theVector, std::vector<T> &expected, int row,
                   int col, std::string a_name) {
    std::vector<T> test_vector;
    for (auto i = 0; i < row; i++) {
        for (auto j = 0; j < col; j++) {
//            std::cout << "I: " << i << "\t" << "J: " << j << "\t" <<
//                      new_vector(i, j) << std::endl;
            test_vector.push_back(theVector(i, j));
        }
    }
    testAsssertion(test_vector, expected, a_name);
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
                           std::string name,
                           double timer) {
    mTimingName.push_back(name);
    mTiming.push_back(timer);
    for (int i = 0; i < actual.getColumns(); i++) {
        for (int j = 0; j < actual.getRows(); j++) {
            auto evaluate = expected(i, j) - actual(i, j);
            if (fabs((double) evaluate > tolerance)) {
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
    std::cout
            << "--------------------------------------------------------------"
            << "\n";
};

void tests::testErrorCode(std::string &ErrorType) {
    mErrors.push_back(ErrorType);
}

template<typename T>
std::vector<T> tests::vectorGen(matrix<T> &array) {
    int dims = (array.getColumns() * array.getRows());
    std::vector<T> vector(dims);
    return vector;
}

void tests::timing() {
    for (unsigned int i = 0; i < mTiming.size(); i++) {
        std::cout << "Function: " << std::setprecision(9) << mTimingName.at(i)
                  << "\t" << "Timing: "
                  << std::setprecision(9) << mTiming.at(i) * 1000 << std::endl;
    }
}
