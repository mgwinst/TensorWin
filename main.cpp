#include <iostream>
#include <print>

#include "core/tensor.h"

int main() {
    Tensor<float> a = Tensor<float>::arange(12).reshape({3, 2, 2});
    Tensor<float>::print(a);
}
