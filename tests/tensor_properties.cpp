#include <gtest/gtest.h>
#include "../core/tensor.h"

TEST(TensorProperties, Size) {
    Tensor<float> t1({1024});   
    EXPECT_EQ(t1.size(), 1024);

    Tensor<float> t2({32, 32});   
    EXPECT_EQ(t2.size(), 1024);

    Tensor<float> t3({4, 4, 4});   
    EXPECT_EQ(t3.size(), 64);

    Tensor<float> t4({4, 4, 4, 4});   
    EXPECT_EQ(t4.size(), 256);
}

TEST(TensorProperties, NumberOfBytes) {
    Tensor<float> t1({32});   
    EXPECT_EQ(t1.nbytes(), 32 * (sizeof(float)));

    Tensor<int> t2({32});   
    EXPECT_EQ(t2.nbytes(), 32 * (sizeof(int)));
}

TEST(TensorProperties, Strides) {
    Tensor<float> t1({64});
    auto strides1 = t1.strides();
    EXPECT_EQ(strides1[0], 1);

    Tensor<float> t2({10, 10});
    auto strides2 = t2.strides();
    EXPECT_EQ(strides2[0], 10);
    EXPECT_EQ(strides2[1], 1);
    
    Tensor<float> t3({3, 4, 4});
    auto strides3 = t3.strides();
    EXPECT_EQ(strides3[0], 16);
    EXPECT_EQ(strides3[1], 4);
    EXPECT_EQ(strides3[2], 1);
}

TEST(TensorProperties, Shape) {
    Tensor<float> t1({10});
    auto shape1 = t1.shape();
    EXPECT_EQ(shape1[0], 10);

    Tensor<float> t2({8, 4, 4});
    auto shape2 = t2.shape();
    EXPECT_EQ(shape2[0], 8);
    EXPECT_EQ(shape2[1], 4);
    EXPECT_EQ(shape2[2], 4);
}

TEST(TensorProperties, ShapeSpecificDim) {
    Tensor<float> t1({8, 4, 4});
    EXPECT_EQ(t1.shape(0), 8);
    EXPECT_EQ(t1.shape(1), 4);
    EXPECT_EQ(t1.shape(2), 4);
}



