#pragma once

#include <vector>
#include <numeric>

int get_size_from_shape(const std::vector<int>&);
std::vector<int> get_strides_from_shape(const std::vector<int>&);

struct View {
    std::vector<int> shape;
    std::vector<int> strides;
    // int offset;
    int size;
    
    View(const std::vector<int>&);

    View() = delete;
    View(const View&);
    View(View&&);
    View& operator=(const View&);
    View& operator=(View&&);


};

