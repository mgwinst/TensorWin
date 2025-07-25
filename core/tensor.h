#pragma once

#include <memory>
#include <print>
#include <cmath>
#include <span>
#include <ranges>
#include <execution>

#include "buffer.h"
#include "view.h"
#include "concepts.h"
#include "utils.h"

template <typename T> 
struct Tensor {
    View view;
    std::shared_ptr<Buffer<T>> buffer;

    Tensor(const std::vector<std::size_t>& shape) :
        view{ shape },
        buffer{ std::make_shared<Buffer<T>>(common::get_size_from_shape(shape)) } {}

    // want the option to specifiy a buffer (e.g. reshape())
    Tensor(const std::vector<std::size_t>& shape, std::shared_ptr<Buffer<T>> new_buffer) noexcept : 
        view{ shape }, 
        buffer{ new_buffer } {}

    Tensor(const Tensor& other) : 
        view{ other.view },
        buffer{ other.buffer } {}
   
    Tensor& operator=(const Tensor& other) {
        if (this != &other) {
            view = other.view;
            buffer = other.buffer;
        }
        return *this;
    }

    Tensor(Tensor&& other) : 
        view{ std::move(other.view) },
        buffer{ std::move(other.buffer) } {}

    Tensor& operator=(Tensor&& other) {
        if (this != &other) {
            view = std::move(other.view);
            buffer = std::move(other.buffer);
        }
        return *this;
    }










    static Tensor<T> zeros(const std::vector<std::size_t>& shape) {
        Tensor<T> t{ shape };
        std::ranges::fill(t.buffer->data, 0);
        return t;
    }
    
    static Tensor<T> ones(const std::vector<std::size_t> shape) {
        Tensor<T> t{ shape };
        std::ranges::fill(t.buffer->data, 1);
        return t;
    }
    
    static Tensor<T> full(const std::vector<std::size_t>& shape, T fill_value) {
        Tensor<T> t{ shape };
        std::ranges::fill(t.buffer->data, fill_value);
        return t;
    }
    
    static Tensor<T> arange(std::size_t size) {
        Tensor<T> t{ {size} };
        std::views::iota(t.buffer->data, 0);
        return t;
    }
    
    static Tensor<T> linspace(float start, float stop, std::size_t steps) {
        Tensor<T> t{ {steps} };
        auto step_size = (stop - start) / (steps - 1);
        t.buffer->data.at(0) = start;

        for (std::size_t i = 1; i < t.size(); i++) {
            t.buffer->data.at(i) = t.buffer->data.at(i-1) + step_size; 
        }
        return t;
    }

    static Tensor<T> eye(std::size_t n, std::optional<std::size_t> m = std::nullopt) {
        if (m.has_value()) {
            if (n <= 0 || m.value() <= 0) throw std::invalid_argument("dims must be positive");
            Tensor<T> t{{n, m.value()}}; 
            std::size_t i = 0;
            for (std::size_t j = 0; j < t.view.shape[0]; j++) {
                if (i == t.view.shape[1]) break;
                t.buffer->data.at(t.view.strides[0] * j + (i++)) = 1;
            }
            return t;
        } else {
            if (n <= 0) throw std::invalid_argument("dims must be positive");
            Tensor<T> t{{n, n}};
            std::size_t i = 0;
            for (std::size_t j = 0; j < t.view.shape[0]; j++) {
                if (i == t.view.shape[1]) break;
                t.buffer->data.at(t.view.strides[0] * j + (i++)) = 1;
            }
            return t;
        }
    }
    
    static Tensor<T> full_like(const Tensor<T>& tensor, std::size_t fill_value) {
        Tensor<T> t{ tensor.shape() };
        std::ranges::fill(t.buffer->data, fill_value);
        return t;
    } 
    
    static Tensor<T> ones_like(const Tensor<T>& tensor) {
        Tensor<T> t{ tensor.shape() };
        std::ranges::fill(t.buffer->data, 1);
        return t;
    } 
    
    static Tensor<T> zeros_like(const Tensor<T>& tensor) {
        Tensor<T> t{ tensor.shape() };
        std::ranges::fill(t.buffer->data, 0);
        return t;
    } 
    
    // reshape() will not change state, but return another Tensor with a new view
    // do we need a view() alias?
    Tensor<T> reshape(const std::vector<std::size_t>& shape) const {
        auto n = std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<>());
        if (size() != n) throw std::invalid_argument("reshape dims mismatch");
        return Tensor<T>{ shape, buffer };
    }
    

    // hopefully printing ranges will work in libstdc++ soon
    /*
    void print() const noexcept {
        std::println("(Tensor -> (shape={}, strides={}, size=[{}]))", sh, st, size());
    }

    void print2D() const noexcept {
        for (std::size_t i = 0; i < size(); i++) {
            if (i % view.strides[0] == 0 && i != 0) std::println();
            std::cout << buffer->data.at(i) << ' ';
        }
        std::println();
    }
    */





    // ops

    // do shapes match? -> do op

    // check broadcastable?
    // expand dims
    // perform element-wise op over new view

    // (1, 4, 2)
    // (4, 1)

    template <typename ExecutionPolicy, typename U>
    requires std::is_execution_policy_v<std::remove_cvref_t<ExecutionPolicy>>
    void add(ExecutionPolicy&& policy, const U& other) {
        if constexpr (std::is_arithmetic_v<U>) {
            std::for_each(policy, buffer->data.begin(), buffer->data.end(), [other](U& elem) { elem += static_cast<U>(other); }); }
        else if constexpr (std::is_same_v<Tensor<T>, U>) {
            if (shape() == other.shape()) {
                std::ranges::transform(policy, buffer->data, other.buffer->data, buffer->data, [](const U a, const U b) { return a + b; });
            } else {
                
            }
        }
    }





    std::vector<std::size_t> shape() const noexcept { return view.shape; }
    std::size_t shape(const std::size_t dim) const noexcept { return view.shape.at(dim); }
    std::vector<std::size_t> strides() const noexcept { return view.strides; }
    std::size_t size() const noexcept { return buffer->data.size(); }
    std::size_t numel() const noexcept { return buffer->data.size(); }
    std::size_t ndim() const noexcept { return view.shape.size(); }
    T* data() const noexcept { return buffer->data.data(); }
    std::size_t element_size() const noexcept { return sizeof(T); }
    std::size_t nbytes() const noexcept { return buffer->data.size() * sizeof(T); }
    
};












