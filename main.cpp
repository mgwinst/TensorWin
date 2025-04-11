#include <iostream>
#include <print>

#include "core/tensor.h"

int main() {
    Tensor<float> a = Tensor<float>::ones({3, 4});
    Tensor<float> b = Tensor<float>::ones({4});
    
    Tensor<float> c = a.add(b);

    for (int i = 0; i < c.size(); i++) {
        std::cout << c.buffer->ptr[i] << ' ';
    }
    std::cout << '\n';



}
