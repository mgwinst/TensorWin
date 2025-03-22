#pragma once

#include <vector>
#include <numeric>

int get_size_from_shape(std::vector<int>&);
std::vector<int> get_strides_from_shape(std::vector<int>&);

class View {
    std::vector<int> shape;
    std::vector<int> strides;
    int size;
   
};

