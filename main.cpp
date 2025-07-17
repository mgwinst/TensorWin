#include <iostream>
#include <print>

#include "tensor.h"

int main() {
    Tensor<float> a = Tensor<float>::ones({3, 4});
    Tensor<float> b = Tensor<float>::ones({4});

    broadcastable(a, b);
    

}
