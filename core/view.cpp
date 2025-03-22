#include <vector>
#include <numeric>

#include "view.h"

int get_size_from_shape(std::vector<int>& shape) {
    if (shape.size() == 1) return shape[0];
    return std::accumulate(std::begin(shape), std::end(shape), 1, std::multiplies<>());
}

std::vector<int> get_strides_from_shape(std::vector<int>& shape) {
    std::vector<int> strides(shape.size());
    int idx = shape.size()-1;
    int acc = 1;
    strides[idx] = acc;   
    while (idx) {
        acc *= shape[idx--];
        strides[idx] = acc;
    }
    return strides;
}