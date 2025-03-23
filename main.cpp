#include <iostream>
#include <print>

#include "core/tensor.h"

int main() {

    Tensor<float> a = Tensor<float>::arange(10);   


    for (auto i = 0; i < a.size(); i++) {
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';
    
}

