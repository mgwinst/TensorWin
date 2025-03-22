#pragma once

#include <memory>

#include "buffer.h"
#include "view.h"
#include "ops.h"

template <typename T>
struct Tensor {
    // View view;
    // std::shared_ptr<Buffer> buffer; 
    // could use std::vector<std::reference_wrapper<Tensor>> , lighweight wrapper around a Tensor&
    std::vector<Tensor*> source; // what are the dependencies of this current Tensor
    Op op; // what particular operation formed this Tensor
    
    Tensor() = default;
};


template <typename T>
Tensor<T> TensorOp(Tensor<T>& t1, Tensor<T>& t2, Op op) {
    Tensor<T> t;
    t.source.push_back(&t1);
    t.source.push_back(&t2);
    t.op = op;

    return t;
}

template <typename T>
Tensor<T> add(Tensor<T>& a, Tensor<T>& b) {
    Tensor<T> t = TensorOp(a, b, Op::ADD);
    return t;
}