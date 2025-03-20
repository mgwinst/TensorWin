#pragma once

#include <memory>
#include <vector>
#include <optional>

struct Tensor {
    View view;
    std::shared_ptr<Buffer> buffer;
    std::optional<std::vector<Ops>> ops;
    std::optional<Parents> parents;  
};

struct View {
    std::vector<int> shape;
    std::vector<int> strides;
    int size;
};

struct Buffer {
    void* bytes;
};

enum class Ops {
    
};


