#pragma once

#include <vector>
#include <numeric>

#include "utils.h"

class View {
public:
    std::vector<std::size_t> shape;
    std::vector<std::size_t> strides;
    // std::size_t offset;
    
    View(const std::vector<std::size_t>&);

    View() = delete;
    View(const View&);
    View(View&&);
    View& operator=(const View&);
    View& operator=(View&&);
};

