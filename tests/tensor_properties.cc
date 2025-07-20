#include <gtest/gtest.h>
#include "../core/tensor.h"

TEST(TensorProperties, size) {
    // check this first
    Tensor<float> t0({32});
    EXPECT_EQ(t0.size(), t0.buffer->data.size());
       
    Tensor<float> a({32});   
    EXPECT_EQ(a.size(), 32);

    Tensor<float> b({32, 32});   
    EXPECT_EQ(b.size(), 1024);

    Tensor<float> c({4, 4, 4});   
    EXPECT_EQ(c.size(), 64);

    Tensor<float> d({4, 4, 4, 4});   
    EXPECT_EQ(d.size(), 256);
}

TEST(TensorProperties, nbytes) {
    Tensor<float> a({32});   
    EXPECT_EQ(a.nbytes(), 32 * (sizeof(float)));

    Tensor<double> b({32});   
    EXPECT_EQ(b.nbytes(), 32 * (sizeof(double)));
}

TEST(TensorProperties, strides) {
    Tensor<float> a({64});
    EXPECT_EQ(a.strides()[0], 1);

    Tensor<float> b({10, 10});
    EXPECT_EQ(b.strides()[0], 10);
    EXPECT_EQ(b.strides()[1], 1);
    
    Tensor<float> c({3, 4, 4});
    EXPECT_EQ(c.strides()[0], 16);
    EXPECT_EQ(c.strides()[1], 4);
    EXPECT_EQ(c.strides()[2], 1);
}

TEST(TensorProperties, shape) {
    Tensor<float> a({10});
    EXPECT_EQ(a.shape()[0], 10);

    Tensor<float> b({8, 4, 4});
    EXPECT_EQ(b.shape()[0], 8);
    EXPECT_EQ(b.shape()[1], 4);
    EXPECT_EQ(b.shape()[2], 4);
}

TEST(TensorProperties, shape_specific_dim) {
    Tensor<float> a({8, 4, 4});
    EXPECT_EQ(a.shape(0), 8);
    EXPECT_EQ(a.shape(1), 4);
    EXPECT_EQ(a.shape(2), 4);
}

TEST(TensorProperties, ndim) {
    Tensor<float> a({8, 4, 4});
    EXPECT_EQ(a.ndim(), 3);

    Tensor<float> b({4, 4});
    EXPECT_EQ(b.ndim(), 2);
}



