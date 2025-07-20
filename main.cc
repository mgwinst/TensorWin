#include <print>

#include "core/tensor.h"
#include "core/buffer.h"

int main() {
    auto t = Tensor<float>::zeros({4, 4});
    for (auto&& x : t.buffer->data) { std::print("{} ", x); }
    std::println();
}
