#ifndef MODIFYRESULT_H
#define MODIFYRESULT_H

#include <cstddef>

enum SortingMethod {
    Empty = 0,
    Bubble = 1,
    Minimum = 2,
    MergeSort = 3,
    QuickSort = 4
};

struct ModifyResult {
    int time;
    std::size_t number;
    SortingMethod sort;

    ModifyResult(int time = 0, size_t number = 0, SortingMethod sort = Empty)
        : time { time }, number { number }, sort { sort } {}
};

#endif // MODIFYRESULT_H
