#pragma once

#include <memory>
#include <iostream>
#include <cmath>

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

    // want the option to specifiy a buffer (e.g. reshape())
    Tensor(const std::vector<int>& shape, std::shared_ptr<Buffer<T>> buff) noexcept : view{shape}, buffer{buff} {}

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

    static Tensor<T> zeros(const std::vector<int>& shape) noexcept {
        Tensor<T> t{shape};
        for (auto i = 0; i < t.size(); i++) {
            t.buffer->data[i] = 0;
        }
        return t;
    }

    static Tensor<T> ones(const std::vector<int>& shape) noexcept {
        Tensor<T> t{shape};
        for (auto i = 0; i < t.size(); i++) {
            t.buffer->data[i] = 1;
        }
        return t;
    }
    
    static Tensor<T> full(const std::vector<int>& shape, T fill_value) noexcept {
        Tensor<T> t{shape};
        for (auto i = 0; i < t.size(); i++) {
            t.buffer->data[i] = fill_value;
        }
        return t;
    }

    static Tensor<T> arange(int size) noexcept {
        Tensor<T> t{{size}};
        for (auto i = 0; i < t.size(); i++) {
            t.buffer->data[i] = i;
        }
        return t;
    }

    static Tensor<T> linspace(float start, float stop, int steps) noexcept {
        Tensor<T> t{{steps}};
        auto step_size = (stop - start) / (steps-1);
        t.buffer->data[0] = start;
        for (auto i = 1; i < t.size(); i++) {
            t.buffer->data[i] = t.buffer->data[i-1] + step_size; 
        }
        return t;
    }

    // CLEAN THIS UP
    static Tensor<T> eye(int n, std::optional<int> m = std::nullopt) {
        if (m.has_value()) {
            if (n <= 0 || m.value() <= 0) throw std::invalid_argument("dims must be positive");
            Tensor<T> t{{n, m.value()}}; 
            int i = 0;
            for (auto j = 0; j < t.view.shape[0]; j++) {
                if (i == t.view.shape[1]) break;
                t.buffer->data[t.view.strides[0] * j + (i++)] = 1;
            }
            return t;
        } else {
            if (n <= 0) throw std::invalid_argument("dims must be positive");
            Tensor<T> t{{n, n}};
            int i = 0;
            for (auto j = 0; j < t.view.shape[0]; j++) {
                if (i == t.view.shape[1]) break;
                t.buffer->data[t.view.strides[0] * j + (i++)] = 1;
            }
            return t;
        }
    }  

    static Tensor<T> full_like(const Tensor<T>& tensor, int fill_value) {
        Tensor<T> t{tensor.view.shape};
        for (int i = 0; i < t.size(); i++) {
            t.buffer->data[i] = fill_value;
        }
        return t;
    } 

    static Tensor<T> ones_like(const Tensor<T>& tensor) {
        Tensor<T> t{tensor.view.shape};
        for (int i = 0; i < t.size(); i++) {
            t.buffer->data[i] = 1;
        }
        return t;
    } 
    
    static Tensor<T> zeros_like(const Tensor<T>& tensor) {
        Tensor<T> t{tensor.view.shape};
        for (int i = 0; i < t.size(); i++) {
            t.buffer->data[i] = 0;
        }
        return t;
    } 

    // reshape() will not change state, but return another Tensor with a new view
    // do we need a view() alias?
    Tensor<T> reshape(const std::vector<int>& shape) const {
        auto n = std::accumulate(std::begin(shape), std::end(shape), 1, std::multiplies<>());
        if ((*this).size() != (n)) throw std::invalid_argument("reshape dims mismatch");
        return Tensor<T>{shape, (*this).buffer};
        
    }

    // print tensor information
    static void print(Tensor<T>& tensor) {
        std::println("(Tensor -> (shape={}, strides={}, size=[{}]))", tensor.view.shape, tensor.view.strides, tensor.size());
    }

    // little debug helper, will remove later
    static void print2D(Tensor<T>& tensor) {
        for (int i = 0; i < tensor.size(); i++) {
            if (i % tensor.view.strides[0] == 0 && i != 0) std::cout << "\n";
            std::cout << tensor.buffer->data[i] << ' ';
        }
        std::cout << '\n';
    }

    // Tensor properties
    std::vector<int> shape() const noexcept { return view.shape; }
    int shape(const int dim) const noexcept { return view.shape.at(dim); }

    std::vector<int> strides() const noexcept { return view.strides; }
    int size() const noexcept { return buffer->size; }
    T* data() const noexcept { return buffer->data; }
    int nbytes() const noexcept { return buffer->size * sizeof(T); }
    int numel() const noexcept { return buffer->size; }
    int element_size() const noexcept { return sizeof(T); }
    
       
};
