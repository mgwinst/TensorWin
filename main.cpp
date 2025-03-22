#include <iostream>

#include "include/tensor.h"

int main() {
    Tensor<float> a;
    Tensor<float> b;

    Tensor<float> c = add(a, b);
    
    for (int i = 0; i < 2; i++) {
        std::cout << c.source[i] << '\n';
    }

    std::cout << '\n';

    std::cout << (int)c.op << std::endl;

}

