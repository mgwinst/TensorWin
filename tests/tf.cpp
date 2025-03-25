#include <print>
#include "../core/concepts.h"

template <typename... Ts>
auto func1(const Ts&... args) {
    auto tuple = std::tie(args...);
    return tuple;
}

template <typename... Ts> 
void func2(const Ts&... idxs) {
    std::print("{}\n", sizeof...(idxs));
}

int main() {


}   


