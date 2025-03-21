#pragma once

#include <variant>

#include "buffer.h"
#include "view.h"
#include "ops.h"

template <typename T>
struct Tensor {
    View view;
    std::shared_ptr<Buffer<T>> buffer;
    std::vector<Tensor*> source; 
    Op op;
    
};

template <typename T>
Tensor<T> TensorOp(Tensor<T>& a, Tensor<T>& b, Op op) {
    Tensor t;
    t.source.push_back(a);
    t.source.push_back(b);
    t.op = op;


}