#pragma once

#include <numeric>
#include <vector>
#include <utility>

#include "tensor.h"

inline std::size_t get_size_from_shape(const std::vector<std::size_t>& shape) {
    if (shape.size() == 1) return shape[0];
    return std::accumulate(std::begin(shape), std::end(shape), 1, std::multiplies<>());
}

inline std::vector<std::size_t> get_strides_from_shape(const std::vector<std::size_t>& shape) {
    std::vector<std::size_t> strides(shape.size());
    std::size_t index = shape.size() - 1;
    std::size_t acc = 1;
    strides[index] = acc;   
    while (index) {
        acc *= shape[index--];
        strides[index] = acc;
    }
    return strides;
}

template <typename T>
std::pair<const Tensor<T>&, const Tensor<T>&> 
find_larger_smaller(const Tensor<T>& t1, const Tensor<T>& t2) {
    return (t1.ndim() >= t2.ndim()) ? std::make_pair(t1, t2) : std::make_pair(t2, t1);
}

template <typename T>
inline void broadcastable(const Tensor<T>& t1, const Tensor<T>& t2) {
    auto [larger, smaller] = find_larger_smaller(t1, t2);   
    auto dim_diff = larger.ndim() - smaller.ndim();

    std::vector<T> tmp = smaller.view.shape();
    tmp.insert(tmp.begin(), dim_diff, 1);

    std::print("{}\n", larger.shape());
    std::print("{}\n", tmp);

    
}



