#pragma once

template <typename T>
struct Buffer {
    T* data = nullptr;
    int size = 0;
};