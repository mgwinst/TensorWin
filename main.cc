#include <iostream>
#include <print>

#include "core/tensor.h"
#include "core/buffer.h"

int main() {
    Buffer<int> buff{ 10 };
    std::print("{}\n", buff.data.size());
    std::print("{}\n", buff.data.capacity());
    std::print("{}\n", buff.data);
}
