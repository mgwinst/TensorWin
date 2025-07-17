#include <iostream>
#include <print>

#include "core/tensor.h"

int main() {
    Tensor<float> a = Tensor<float>::ones({3, 16, 4});
    Tensor<float> b = Tensor<float>::ones({1, 3});

    a.print();
    b.print();

    std::println();

    std::print("{}\n", broadcastable(a, b));
    

}
