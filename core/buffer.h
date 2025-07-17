#pragma once

#include <new>
#include <cassert>
#include <exception>
#include <iostream>
#include <numeric>
#include <memory>

// in future, decouple buffer and alignment logic
template <typename T>
struct BufferAllocator {
    
};

template <typename T>
class Buffer {
public:
    constexpr static std::size_t align_val{ 32 };
    constexpr static std::align_val_t alignment{ align_val };

    T* ptr{ nullptr };
    std::size_t capacity{}; 
    std::size_t size{};

    Buffer() : ptr{ nullptr }, capacity{ 0 }, size{ 0 } {}

    explicit Buffer(std::size_t n) {
        if (n > max_size() || n <= 0) throw std::bad_array_new_length();
        size = n;
        capacity = ((n + align_val - 1) & ~(align_val - 1)); // round to nearest multiple of 32
        ptr = static_cast<T*>(::operator new[](capacity * sizeof(T), alignment));
        if (!ptr) throw std::bad_alloc();
    }

    ~Buffer() noexcept { ::operator delete[](ptr, capacity * sizeof(T), alignment); }
    
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;
    Buffer(Buffer&&) = delete;
    Buffer& operator=(Buffer&&) = delete;

    [[nodiscard]] std::size_t max_size() const noexcept { return std::numeric_limits<std::size_t>::max() / sizeof(T); }

};

template <typename T>
[[nodiscard]] std::shared_ptr<Buffer<T>> create_buffer(std::size_t size) {
    return std::make_shared<Buffer<T>>(size);
}


