#ifndef MODIFYRESULT_H
#define MODIFYRESULT_H

#include <cstddef>

enum SortingAlgorithm {
    Empty = 0,
    Bubble = 1,
    Minimum = 2,
    MergeSort = 3,
    QuickSort = 4
};

struct ModifyResult {
    size_t speed;
    size_t number;
    SortingAlgorithm algorithm;

    ModifyResult(size_t speed = 0, size_t number = 0, SortingAlgorithm algorithm = Empty)
        : speed { speed }, number { number }, algorithm { algorithm } {}

    bool isValid() const noexcept
    {
        return algorithm;
    }
};

#endif // MODIFYRESULT_H
