#ifndef SORTINGPARAMETERS_H
#define SORTINGPARAMETERS_H

#include <cstddef>

enum SortingAlgorithm {
    Empty = 0,
    BubbleSort = 1,
    MinimumSort = 2,
    MergeSort = 3,
    QuickSort = 4
};

struct SortingParameters {
    size_t speed;
    size_t number;
    SortingAlgorithm algorithm;

    SortingParameters(size_t speed = 0, size_t number = 0, SortingAlgorithm algorithm = Empty)
        : speed { speed }, number { number }, algorithm { algorithm } {}

    bool isValid() const noexcept
    {
        return algorithm;
    }
};

#endif // SORTINGPARAMETERS_H
