#pragma once

#include <numeric>
#include <vector>
#include <utility>
#include <ranges>
#include <span>

template <typename T>
class Tensor;

inline std::size_t get_size_from_shape(std::span<const std::size_t> shape) {
    if (shape.empty()) return 0;
    if (shape.size() == 1) return shape[0];
    return std::accumulate(std::begin(shape), std::end(shape), 1, std::multiplies<>());
}

inline std::vector<std::size_t> get_strides_from_shape(std::span<const std::size_t> shape) {
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
std::pair<const Tensor<T>&, const Tensor<T>&> find_larger_smaller(const Tensor<T>& t1, const Tensor<T>& t2) {
    if (t1.ndim() >= t2.ndim()) return {t1, t2};
    else return {t2, t1};
}

template <typename T>
bool broadcastable(const Tensor<T>& t1, const Tensor<T>& t2) {
    auto&& [larger, smaller] = find_larger_smaller(t1, t2);   
    auto dim_diff = larger.ndim() - smaller.ndim();

    auto larger_dims = larger.shape();
    auto smaller_dims = smaller.shape();

    smaller_dims.insert(smaller_dims.begin(), dim_diff, 1);

    auto rev_zip_dims = std::views::zip(larger_dims, smaller_dims) | std::views::reverse;

    for (auto&& [dim1, dim2] : rev_zip_dims) {
        if (dim1 == dim2 || (dim1 == 1 || dim2 == 1)) continue;
        else return false;
    }

    return true;
}


