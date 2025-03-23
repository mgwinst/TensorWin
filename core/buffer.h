#pragma once

#include <cstdlib>
#include <cassert>
#include <exception>

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
    
    // can't copy buffers directly, tensors will pass copy shared_ptr<Buffer> to eachother
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;

    Buffer(Buffer&& other) noexcept : data{other.data} , size{other.size} {
        other.data = nullptr;
        other.size = 0;
        std::cout << "Buffer: called move constructor\n";
    }

    Buffer& operator=(Buffer&& other) noexcept {
        delete[] data;
        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;
        std::cout << "Buffer: called move assignment\n";
        return *this;
    }

    int num_bytes() const noexcept { return size * sizeof(T); }
    
};
