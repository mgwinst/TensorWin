#include <iostream>
#include <print>

#include "core/tensor.h"
#include "core/buffer.h"

int main() {
    auto t = Tensor<double>::ones({4, 4});
    for (auto&& x : t.buffer->data) {
        std::print("{} ", x);
    }
}
