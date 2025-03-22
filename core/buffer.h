#pragma once

#include <cstdlib>

template <typename T>
class Buffer {
    T* data = nullptr;
    int size = 0;

public:
    Buffer(int sz) noexcept : size{sz} {
        static_assert(sz > 0);
        data = std::aligned_alloc(32, sz * sizeof(T));
    }

    ~Buffer() noexcept { std::free(data); }

    Buffer() = delete;
    Buffer(const Buffer&) = delete;
    Buffer(Buffer&&) = delete;
    Buffer& operator=(Buffer&&) = delete;
    Buffer& operator=(Buffer&&) = delete;
};
