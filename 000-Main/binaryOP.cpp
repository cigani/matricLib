//
// Created by jam on 26-Jul-17.
//

#include "binaryOP.hpp"

template<typename T>
void
binaryOP::add(T *mat1, T *mat2, int &rank1, int &rank2, std::vector<T> &home) {
    int smaller = (rank1 > rank2) ? rank2 : rank1;
    int larger = (rank1 > rank2) ? rank1 : rank2;
    for (int i = 0; i < smaller; i++) {
        home.push_back(mat1[i] + mat2[i]);
    }
    if (smaller != larger) {
        if (smaller == rank1) {
            for (int j = smaller; j < larger; ++j) {
                home.push_back(mat2[j]);
            }
        } else if (smaller == rank2) {
            for (int j = smaller; j < larger; ++j) {
                home.push_back(mat1[j]);
            }
        } else {};
    }
}

template<typename T>
void binaryOP::subtract(T *mat1, T *mat2, int &rank1, int &rank2,
                        std::vector<T> &home) {
    int smaller = (rank1 > rank2) ? rank2 : rank1;
    int larger = (rank1 > rank2) ? rank1 : rank2;
    for (int i = 0; i < smaller; i++) {
        home.push_back(mat1[i] - mat2[i]);
    }
    if (smaller != larger) {
        if (smaller == rank1) {
            for (int j = smaller; j < larger; ++j) {
                home.push_back(-mat2[j]);
            }
        } else if (smaller == rank2) {
            for (int j = smaller; j < larger; ++j) {
                home.push_back(-mat1[j]);
            }
        } else {};
    }
};
