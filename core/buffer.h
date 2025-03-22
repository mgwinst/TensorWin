#pragma once

#include <cstdlib>
#include <cassert>

template <typename T>
struct Buffer {
    T* data = nullptr;
    int size = 0;

    Buffer(int sz) noexcept : size{sz} {
        assert(sz > 0);
        data = (T*)std::aligned_alloc(32, sz * sizeof(T));
    }

    ~Buffer() noexcept { std::free(data); }

    Buffer() = delete;
    Buffer(const Buffer&) = delete;
    Buffer(Buffer&&) = delete;
    Buffer& operator=(Buffer&) = delete;
    Buffer& operator=(Buffer&&) = delete;

    T* get_data() const noexcept { return data; }
    int num_bytes() const noexcept { return size * sizeof(T); }
    
};
