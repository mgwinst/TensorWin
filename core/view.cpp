#include <vector>
#include <numeric>
#include <iostream>

#include "view.h"

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

View::View(const std::vector<int>& shape) :
    shape{shape},
    strides{get_strides_from_shape(shape)},
    size{get_size_from_shape(shape)} {}

View::View(const View& other) : 
    shape{other.shape},
    strides{other.strides},
    size{other.size} {}
 
View& View::operator=(const View& other) {
    shape = other.shape;
    strides = other.strides;
    size = other.size;
    return *this;
}

View::View(View&& other) : 
    shape{std::move(other.shape)},
    strides{std::move(other.strides)},
    size{other.size} {
        // clearing the old vectors, necessary?
        other.shape.clear();
        other.strides.clear();
        other.size = 0;
    }

View& View::operator=(View&& other) {
    shape = std::move(other.shape);
    strides = std::move(other.strides);
    size = other.size;
    other.shape.clear();
    other.strides.clear();
    other.size = 0;
    return *this;
}