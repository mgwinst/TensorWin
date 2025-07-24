#pragma once

#include <new>
#include <cassert>
#include <exception>
#include <iostream>
#include <numeric>
#include <memory>

template <typename T>
struct BufferAllocator {
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;   

    template <typename U>
    struct rebind { 
        using other = BufferAllocator<U>;
    };

    BufferAllocator() noexcept = default;

    BufferAllocator(const BufferAllocator&) noexcept = default; 
    BufferAllocator& operator=(const BufferAllocator&) noexcept = default; 
    
    template <typename U>
    BufferAllocator(const BufferAllocator<U>& other) noexcept {}

    template <typename U>
    BufferAllocator& operator=(const BufferAllocator<U>& other) noexcept {}

    BufferAllocator(BufferAllocator&&) noexcept = delete;
    BufferAllocator& operator=(BufferAllocator&&) noexcept = delete;

    [[nodiscard]] T* allocate(std::size_t n) {
        if (n > max_size() || n < 0) throw std::bad_array_new_length();
        T* ptr = static_cast<T*>(::operator new(n * sizeof(T)));
        if (!ptr) throw std::bad_alloc();
        return ptr;
    }

    // vector<>::size() being passed to n?
    void deallocate(T* ptr, std::size_t n) noexcept { ::operator delete(ptr); }

    [[nodiscard]] std::size_t max_size() const noexcept { return std::numeric_limits<std::size_t>::max() / sizeof(T); }
    
};

template <typename T, typename U>
bool operator==(const BufferAllocator<T>&, const BufferAllocator<U>&) { return true; }

template <typename T, typename U>
bool operator!=(const BufferAllocator<T>&, const BufferAllocator<U>&) { return false; }

template <typename T> 
struct Buffer {   
    std::vector<T, BufferAllocator<T>> data;

    Buffer(std::size_t n) : data(n) {}

    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;
    Buffer(Buffer&&) = delete;
    Buffer& operator=(Buffer&&) = delete;

};

template <typename T>
[[nodiscard]] std::shared_ptr<Buffer<T>> create_buffer(std::size_t size) {
    return std::make_shared<Buffer<T>>(size);
}

