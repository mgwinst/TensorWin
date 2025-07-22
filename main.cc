#include <print>

#include "core/tensor.h"
#include "core/buffer.h"
#include "core/utils.h"

int main() {
    auto a = Tensor<double>::ones({2, 4, 8});
    auto b = Tensor<double>::ones({8});

    a.add(b);
    for (auto x : a.buffer->data) { std::print("{} ", x); }
    std::println();

    /*
    // how do I know which tensor this view is for? a or b?
    std::optional<View> v = common::broadcastable(a, b);
    
    if (v.has_value()) {
        v.value().print();
    }
    */

    
    
}
