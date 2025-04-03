#include <gtest/gtest.h>
#include "../core/tensor.h"

TEST(TensorFunctions, reshape) {
    Tensor<float> a({2, 3, 2});
    Tensor<float> b = a.reshape({4, 3});
    
    EXPECT_EQ(a.buffer, b.buffer);
    EXPECT_EQ(b.size(), a.size());
    EXPECT_EQ(b.shape()[0], 4);
    EXPECT_EQ(b.shape()[1], 3);
}

TEST(TensorFunctions, zeros) {
    int size = 32;
    auto a = Tensor<float>::zeros({size});
    for (auto i = 0; i < size; i++) {
        EXPECT_EQ(a.buffer->data[i], 0);
    }
}

TEST(TensorFunctions, ones) {
    int size = 32;
    auto a = Tensor<float>::ones({size});
    for (auto i = 0; i < size; i++) {
        EXPECT_EQ(a.buffer->data[i], 1);
    }
}

TEST(TensorFunctions, linspace) {
    auto a = Tensor<float>::linspace(0, 10, 5);
    EXPECT_EQ(a.buffer->data[0], 0.0);
    EXPECT_EQ(a.buffer->data[1], 2.5);
    EXPECT_EQ(a.buffer->data[2], 5.0);
    EXPECT_EQ(a.buffer->data[3], 7.5);
    EXPECT_EQ(a.buffer->data[4], 10.0);

    a = Tensor<float>::linspace(-10, 10, 5);
    EXPECT_EQ(a.buffer->data[0], -10.0);
    EXPECT_EQ(a.buffer->data[1], -5.0);
    EXPECT_EQ(a.buffer->data[2], 0.0);
    EXPECT_EQ(a.buffer->data[3], 5.0);
    EXPECT_EQ(a.buffer->data[4], 10.0);
}

// do this later
TEST(TensorFunctions, eye) {
    auto a = Tensor<float>::eye(3);
    
}

TEST(TensorFunctions, full_like) {
    Tensor<float> a({4, 4});
    auto b = Tensor<float>::full_like(a, 3);
    
    EXPECT_EQ(a.shape(), b.shape());
    EXPECT_EQ(a.strides(), b.strides());
    EXPECT_EQ(a.size(), b.size());
    
    for (auto i = 0; i < 16; i++) {
        EXPECT_EQ(b.buffer->data[i], 3);
    }
}

TEST(TensorFunctions, ones_like) {
    Tensor<float> a({4, 4});
    auto b = Tensor<float>::ones_like(a);
    
    EXPECT_EQ(a.shape(), b.shape());
    EXPECT_EQ(a.strides(), b.strides());
    EXPECT_EQ(a.size(), b.size());
    
    for (auto i = 0; i < 16; i++) {
        EXPECT_EQ(b.buffer->data[i], 1);
    }
}

TEST(TensorFunctions, zeros_like) {
    Tensor<float> a({4, 4});
    auto b = Tensor<float>::zeros_like(a);
    
    EXPECT_EQ(a.shape(), b.shape());
    EXPECT_EQ(a.strides(), b.strides());
    EXPECT_EQ(a.size(), b.size());
    
    for (auto i = 0; i < 16; i++) {
        EXPECT_EQ(b.buffer->data[i], 0);
    }
}






