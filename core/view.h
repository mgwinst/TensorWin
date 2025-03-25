#pragma once

#include <vector>
#include <numeric>

#include "utils.h"

struct View {
    std::vector<int> shape;
    std::vector<int> strides;
    // int offset;
    
    View(const std::vector<int>&);

    View() = delete;
    View(const View&);
    View(View&&);
    View& operator=(const View&);
    View& operator=(View&&);
};

