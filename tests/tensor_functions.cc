#include <gtest/gtest.h>
#include "../core/tensor.h"

TEST(TensorCreation, construct_from_shape) {
    Tensor<float> a({2, 3, 2});
    Tensor<float> b{a.shape()};

    EXPECT_EQ(b.shape(), a.shape());
    EXPECT_EQ(b.size(), a.size());
    EXPECT_EQ(b.shape()[0], 2);
    EXPECT_EQ(b.shape()[1], 3);
    EXPECT_EQ(b.shape()[2], 2);
}

TEST(TensorCreation, assign_reshape) {
    Tensor<float> a({2, 3, 2});
    Tensor<float> b = a.reshape({4, 3});
    
    EXPECT_EQ(a.buffer, b.buffer);
    EXPECT_EQ(b.size(), a.size());
    EXPECT_EQ(b.shape()[0], 4);
    EXPECT_EQ(b.shape()[1], 3);
}

TEST(TensorCreation, reshape_and_assign_to_self) {
    Tensor<float> a({2, 3, 2});
    a = a.reshape({3, 2, 2});
    
    EXPECT_EQ(a.shape()[0], 3);
    EXPECT_EQ(a.shape()[1], 2);
    EXPECT_EQ(a.shape()[2], 2);

    EXPECT_EQ(a.strides()[0], 4);
    EXPECT_EQ(a.strides()[1], 2);
    EXPECT_EQ(a.strides()[2], 1);
}

TEST(TensorCreation, zeros) {
    std::size_t size = 32;
    auto a = Tensor<float>::zeros({size});
    
    for (auto&& elem : a.buffer->data) {
        EXPECT_EQ(elem, 0.0);
    }
}

TEST(TensorCreation, ones) {
    std::size_t size = 32;
    auto a = Tensor<float>::ones({size});
    
    for (auto&& elem : a.buffer->data) {
        EXPECT_EQ(elem, 1.0);
    }
}

TEST(TensorCreation, linspace) {
    auto a = Tensor<float>::linspace(0, 10, 5);
    EXPECT_EQ(a.buffer->data.at(0), 0.0);
    EXPECT_EQ(a.buffer->data.at(1), 2.5);
    EXPECT_EQ(a.buffer->data.at(2), 5.0);
    EXPECT_EQ(a.buffer->data.at(3), 7.5);
    EXPECT_EQ(a.buffer->data.at(4), 10.0);

    a = Tensor<float>::linspace(-10, 10, 5);
    EXPECT_EQ(a.buffer->data.at(0), -10.0);
    EXPECT_EQ(a.buffer->data.at(1), -5.0);
    EXPECT_EQ(a.buffer->data.at(2), 0.0);
    EXPECT_EQ(a.buffer->data.at(3), 5.0);
    EXPECT_EQ(a.buffer->data.at(4), 10.0);
}

// to do
TEST(TensorCreation, eye) {
    auto a = Tensor<float>::eye(3);
    
}

TEST(TensorCreation, full_like) {
    Tensor<float> a({4, 4});
    auto b = Tensor<float>::full_like(a, 3);
    
    EXPECT_EQ(a.shape(), b.shape());
    EXPECT_EQ(a.strides(), b.strides());
    EXPECT_EQ(a.size(), b.size());
    
    for (auto&& elem : b.buffer->data) {
        EXPECT_EQ(elem, 3);
    }
}

TEST(TensorCreation, ones_like) {
    Tensor<float> a({4, 4});
    auto b = Tensor<float>::ones_like(a);
    
    EXPECT_EQ(a.shape(), b.shape());
    EXPECT_EQ(a.strides(), b.strides());
    EXPECT_EQ(a.size(), b.size());
    
    for (auto&& elem : b.buffer->data) {
        EXPECT_EQ(elem, 1);
    }
}

TEST(TensorCreation, zeros_like) {
    Tensor<float> a({4, 4});
    auto b = Tensor<float>::zeros_like(a);
    
    EXPECT_EQ(a.shape(), b.shape());
    EXPECT_EQ(a.strides(), b.strides());
    EXPECT_EQ(a.size(), b.size());

    for (auto&& elem : b.buffer->data) {
        EXPECT_EQ(elem, 0);
    }
}






