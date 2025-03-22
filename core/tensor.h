#pragma once

#include <memory>

#include "buffer.h"
#include "view.h"
#include "ops.h"

template <typename T>
struct Tensor {
    View view;
    std::shared_ptr<Buffer<T>> buffer; 

    Tensor(const std::vector<int>& shape) :
    view{shape}, 
    buffer{std::make_shared<Buffer<T>>(get_size_from_shape(shape))} 
    {}

    std::vector<int> shape() const noexcept { return view.shape; }
    std::vector<int> strides() const noexcept { return view.strides; }
    int size() const noexcept { return buffer->size; }
    T* data() const noexcept { return buffer->get_data(); }
    int nbytes() const noexcept { return buffer->num_bytes(); }
    int numel() const noexcept { return view.size; }
    int element_size() const noexcept { return sizeof(T); }
    
    

    
};
