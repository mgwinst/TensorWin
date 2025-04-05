// helpers
#include <numeric>
#include <vector>
#include "utils.h"

std::size_t get_size_from_shape(const std::vector<std::size_t>& shape) {
    if (shape.size() == 1) return shape[0];
    return std::accumulate(std::begin(shape), std::end(shape), 1, std::multiplies<>());
}

std::vector<std::size_t> get_strides_from_shape(const std::vector<std::size_t>& shape) {
    std::vector<std::size_t> strides(shape.size());
    std::size_t index = shape.size()-1;
    std::size_t acc = 1;
    strides[index] = acc;   
    while (index) {
        acc *= shape[index--];
        strides[index] = acc;
    }
    return strides;
}