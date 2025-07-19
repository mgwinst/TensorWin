#include <vector>
#include <numeric>
#include <iostream>

#include "view.h"
#include "utils.h"

View::View(std::span<const std::size_t> shape) :
    shape{ std::ranges::to<std::vector<std::size_t>>(shape) },
    strides{ get_strides_from_shape(shape) } {}

View::View(const View& other) : 
    shape{ other.shape },
    strides{ other.strides } {}
 
View& View::operator=(const View& other) {
    if (this != &other) {
        shape = other.shape;
        strides = other.strides;
    }
    return *this;
}

View::View(View&& other) : 
    shape{ std::move(other.shape) },
    strides{ std::move(other.strides) }
    {
        // clearing the old vectors, necessary?
        other.shape.clear();
        other.strides.clear();
    }

View& View::operator=(View&& other) {
    if (this != &other) {
        shape = std::move(other.shape);
        strides = std::move(other.strides);
        other.shape.clear();
        other.strides.clear();
    }
    return *this;
}
