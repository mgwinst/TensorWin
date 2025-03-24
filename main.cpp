#include <iostream>
#include <print>

#include "core/tensor.h"

int main() {

    // Tensor<float> a = Tensor<float>::arange(10);   
    Tensor<float> a = Tensor<float>::arange(10);
    Tensor<float> b = a;

    Tensor<float>::print(a);
    std::print("{}\n", a.buffer->data[5]);

    Tensor<float>::print(b);
    std::print("{}\n", b.buffer->data[5]);

    // Tensor<float> c = a.reshape(2, 5);


    

    
   

}

