// helpers
#include <numeric>
#include <vector>
#include "utils.h"

int get_size_from_shape(const std::vector<int>& shape) {
    if (shape.size() == 1) return shape[0];
    return std::accumulate(std::begin(shape), std::end(shape), 1, std::multiplies<>());
}

std::vector<int> get_strides_from_shape(const std::vector<int>& shape) {
    std::vector<int> strides(shape.size());
    int index = shape.size()-1;
    int acc = 1;
    strides[index] = acc;   
    while (index) {
        acc *= shape[index--];
        strides[index] = acc;
    }
    return strides;
}