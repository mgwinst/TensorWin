#pragma once

#include <cstdlib>

template <typename T>
struct Buffer {
    T* data = nullptr;
    int size = 0;

    Buffer(int sz) noexcept : size{sz} {
        data = std::aligned_alloc(32, sz * sizeof(T));   
    }

    ~Buffer() { std::free(data); }
};
