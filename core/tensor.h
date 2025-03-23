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
    view{shape}, buffer{std::make_shared<Buffer<T>>(get_size_from_shape(shape))} {}

    Tensor(const Tensor& other) : view{other.view}, buffer{other.buffer} {}
    Tensor& operator=(const Tensor& other) {
        view = other.view;
        buffer = other.buffer;
    }

    Tensor(Tensor&& other) : view{std::move(other.view)}, buffer{std::move(other.buffer)} {}

    Tensor& operator=(Tensor&& other) {
        view = std::move(other.view);
        buffer = std::move(other.buffer);
        return *this;
    }

    T& operator[](int index) {
        assert(view.shape.size() == 1);
        return buffer->data[index];
    }

    // Creation

    static Tensor<T> arange(int size) noexcept {
        Tensor t{{10}};
        for (auto i = 0; i < t.size(); i++) {
            t.buffer->data[i] = i;
        }
        return t;
    }








    // Tensor properties

    std::vector<int> shape() const noexcept { return view.shape; }
    std::vector<int> strides() const noexcept { return view.strides; }
    int size() const noexcept { return buffer->size; }
    T* data() const noexcept { return buffer->data; }
    int nbytes() const noexcept { return buffer->num_bytes(); }
    int numel() const noexcept { return view.size; }
    int element_size() const noexcept { return sizeof(T); }
    
       
};
