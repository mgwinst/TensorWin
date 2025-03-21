#pragma once

#include <vector>

struct View {
    std::vector<int> shape;
    std::vector<int> strides;
    int size;
};