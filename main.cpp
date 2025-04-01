#include <iostream>
#include <print>

#include "core/tensor.h"

int main() {
    Tensor<float> a = Tensor<float>::arange(12).reshape({3, 2, 2});
    Tensor<float> b = a.reshape({6, 2});

    Tensor<float>::print(a);
    Tensor<float>::print(b);

    std::cout << a.buffer->data << '\n';
    std::cout << b.buffer->data << '\n';
}
