#include <iostream>

#include "core/tensor.h"

int main() {

    Tensor<float> t1({1, 2, 3});

    std::cout << t1.data() << '\n';
    std::cout << t1.nbytes() << '\n';
    std::cout << t1.numel() << '\n';

    std::cout << '(';
    for (auto x : t1.shape()) {
        std::cout << x << ' ';
    }
    std::cout << ')';
    std::cout << '\n';

    std::cout << '(';
    for (auto x : t1.strides()) {
        std::cout << x << ' ';
    }
    std::cout << ')';
    std::cout << '\n';



    
}

