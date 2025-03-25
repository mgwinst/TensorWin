#pragma once

#include <cstdlib>
#include <cassert>
#include <exception>
#include <iostream>

template <typename T>
struct Buffer {
    T* data = nullptr;
    int size = 0;

    Buffer(int sz) noexcept : size{sz} {
        assert(sz > 0);
        data = new T[sz]; // align this memory in the future (std::aligned_alloc())
        assert(data != nullptr);
    }

    ~Buffer() noexcept { delete[] data; }
    
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;
    Buffer(Buffer&&) = delete;
    Buffer& operator=(Buffer&&) = delete;
};
