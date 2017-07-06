//
// Created by jam on 04-Jul-17.
//

#ifndef MATRIX_HELPER_H
#define MATRIX_HELPER_H


#include <vector>
#include <stdexcept>
#include <cmath>

class helper {
public:
    template<typename IntType>
    std::vector<IntType> range(IntType start, IntType stop, IntType step) {
        if (step == IntType(0)) {
            throw std::invalid_argument("step for range must be non-zero");
        }

        std::vector<IntType> result;
        IntType i = start;
        while ((step > 0) ? (i < stop) : (i > stop)) {
            result.push_back(i);
            i += step;
        }

        return result;
    }

    template<typename IntType>
    std::vector<IntType> range(IntType stop) {
        return range(IntType(0), stop, IntType(1));
    }

    template<typename IntType>
    std::vector<IntType> range(IntType start, IntType stop) {
        return range(start, stop, IntType(1));
    }

    template<typename IntType>
    std::vector<std::vector<IntType>> reshape(std::vector<IntType> &array) {
        auto dimension = sqrt(array.size());
        std::vector<std::vector<IntType>> result;
        for (auto n: array) {

        }
    }
};


#endif //MATRIX_HELPER_H
