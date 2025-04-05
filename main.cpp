#include <iostream>
#include <print>

#include "core/tensor.h"

int main() {
    Tensor<float> a = Tensor<float>::ones({32});
    std::print("{}\n", a.size());
    std::print("{}\n", a.buffer->capacity);
    std::cout << a.buffer->ptr[31] << '\n';
    
    


}
