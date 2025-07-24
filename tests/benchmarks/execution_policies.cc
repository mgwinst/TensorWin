#include <print>
#include <execution>
#include <chrono>

#include "core/tensor.h"
#include "core/buffer.h"
#include "core/utils.h"

// clang++ -std=c++23 -ltbb -I../../ execution_policies.cc ../../core/view.cc && ./a.out

using namespace std::chrono;

int main() {
    auto t = Tensor<int>::ones({2048, 2048});

    auto start1 = high_resolution_clock::now();
    t.add(std::execution::seq, 16);
    auto end1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(end1-start1);
    
    auto start2 = high_resolution_clock::now();
    t.add(std::execution::unseq, 16);
    auto end2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(end2-start2);

    auto start3 = high_resolution_clock::now();
    t.add(std::execution::par, 16);
    auto end3 = high_resolution_clock::now();
    auto duration3 = duration_cast<microseconds>(end3-start3);

    auto start4 = high_resolution_clock::now();
    t.add(std::execution::par_unseq, 16);
    auto end4 = high_resolution_clock::now();
    auto duration4 = duration_cast<microseconds>(end4-start4);

    std::println("seq: {}", duration1);
    std::println("unseq: {}", duration2);
    std::println("seq par: {}", duration3);
    std::println("unseq par: {}", duration4);
}

