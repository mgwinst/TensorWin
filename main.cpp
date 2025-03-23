#include <iostream>
#include <print>

#include "core/tensor.h"

int main() {

    Tensor<float> a({4, 4, 32, 32});   

    Tensor<float>::print(a);
   

}

