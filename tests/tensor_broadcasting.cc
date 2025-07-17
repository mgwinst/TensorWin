#include "gtest/gtest.h"

#include "../core/tensor.h"
#include "../core/utils.h"

TEST(TensorBroadcasting, broadcastable) {
    Tensor<float> a = Tensor<float>::ones({4, 16, 16});
    Tensor<float> b = Tensor<float>::ones({1});
    EXPECT_EQ(broadcastable(a, b), true);
    
    Tensor<float> c = Tensor<float>::ones({4, 16, 16});
    Tensor<float> d = Tensor<float>::ones({3});
    EXPECT_EQ(broadcastable(c, d), false);

    Tensor<float> e = Tensor<float>::ones({4, 16, 16});
    Tensor<float> f = Tensor<float>::ones({1, 16});
    EXPECT_EQ(broadcastable(e, f), true);

    Tensor<float> g = Tensor<float>::ones({4, 16, 16});
    Tensor<float> h = Tensor<float>::ones({2, 2});
    EXPECT_EQ(broadcastable(g, h), false);
}