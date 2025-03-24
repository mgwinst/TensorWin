#pragma once

#include <memory>
#include <iostream>

#include "buffer.h"
#include "view.h"
#include "ops.h"
#include "concepts.h"

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
        return *this;
    }

    Tensor(Tensor&& other) : view{std::move(other.view)}, buffer{std::move(other.buffer)} {}

    Tensor& operator=(Tensor&& other) {
        view = std::move(other.view);
        buffer = std::move(other.buffer);
        return *this;
    }
    

       // Creation
    static Tensor<T> arange(int size) noexcept {
        Tensor t{{size}};
        for (auto i = 0; i < t.size(); i++) {
            t.buffer->data[i] = i;
        }
        return t;
    }

    // print tensor information
    static void print(Tensor<T>& tensor) {
        std::println("(Tensor -> (shape={}, strides={}, size=[{}]))", tensor.view.shape, tensor.view.strides, tensor.view.size);
    }

    // reshape() will not change state, but return a new view on current tensor
    





    // Tensor properties

    std::vector<int> shape() const noexcept { return view.shape; }
    int shape(const int dim) const noexcept { return view.shape.at(dim); }



    std::vector<int> strides() const noexcept { return view.strides; }
    int size() const noexcept { return buffer->size; }
    T* data() const noexcept { return buffer->data; }
    int nbytes() const noexcept { return buffer->num_bytes(); }
    int numel() const noexcept { return view.size; }
    int element_size() const noexcept { return sizeof(T); }
    
       
};
