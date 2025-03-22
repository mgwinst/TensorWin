#pragma once

#include <vector>
#include <numeric>

int get_size_from_shape(const std::vector<int>&);
std::vector<int> get_strides_from_shape(const std::vector<int>&);

struct View {
    std::vector<int> shape;
    std::vector<int> strides;
    int size;
    
    View(const std::vector<int>&) noexcept;

    View() = delete;
    View(const View&) = delete;
    View(View&&) = delete;
    View& operator=(const View&) = delete;
    View& operator=(View&&) = delete;


};

