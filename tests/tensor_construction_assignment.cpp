#include <gtest/gtest.h>
#include "../core/tensor.h"

TEST(TensorConstructionAndAssignment, CopyConstructor) {
    Tensor<float> a({4, 4});
    Tensor<float> b = a;

    EXPECT_EQ(a.shape(), b.shape());
    EXPECT_EQ(a.strides(), b.strides());
    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(a.buffer, b.buffer);
    // EXPECT_EQ(a.data(), b.data());

}

TEST(TensorConstructionAndAssignment, CopyAssignment) {
    Tensor<float> a({4, 4});
    Tensor<float> b({4, 128, 128});
    b = a;

    EXPECT_EQ(a.shape(), b.shape());
    EXPECT_EQ(a.strides(), b.strides());
    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(a.buffer, b.buffer);
    // EXPECT_EQ(a.data(), b.data()); // necessary if we already check buffers?
}

TEST(TensorConstructionAndAssignment, MoveConstructor) {
    Tensor<float> a({4, 4});
    auto a_addr = a.data();
    auto a_shape = a.shape();
    auto a_strides = a.strides();

    Tensor<float> b = std::move(a);
    
    EXPECT_EQ(b.data(), a_addr);
    EXPECT_EQ(b.shape(), a_shape);
    EXPECT_EQ(b.strides(), a_strides);
   
    EXPECT_EQ(a.buffer, nullptr);
    EXPECT_EQ(a.view.shape.data(), nullptr);    // this is std::vector::data()
    EXPECT_EQ(a.view.strides.data(), nullptr);

}

TEST(TensorConstructionAndAssignment, MoveAssignment) {
    Tensor<float> a({4, 4});
    Tensor<float> b({10});
    auto a_addr = a.data();
    auto a_shape = a.shape();
    auto a_strides = a.strides();

    b = std::move(a);   

    EXPECT_EQ(b.data(), a_addr);
    EXPECT_EQ(b.shape(), a_shape);
    EXPECT_EQ(b.strides(), a_strides);

    EXPECT_EQ(a.buffer, nullptr);
    EXPECT_EQ(a.view.shape.data(), nullptr);    // this is std::vector::data()
    EXPECT_EQ(a.view.strides.data(), nullptr);

}

TEST(TensorConstructionAndAssignment, MultipleCopyAssignment) { 
    Tensor<float> a({4, 4});
    Tensor<float> b({4, 4});
    Tensor<float> c({4, 4});
    Tensor<float> d({4, 4});

    a = b = c = d;

    EXPECT_EQ(a.shape(), d.shape());
    EXPECT_EQ(a.strides(), d.strides());
    EXPECT_EQ(a.size(), d.size());
    EXPECT_EQ(a.buffer, d.buffer);

    EXPECT_EQ(b.shape(), d.shape());
    EXPECT_EQ(b.strides(), d.strides());
    EXPECT_EQ(b.size(), d.size());
    EXPECT_EQ(b.buffer, d.buffer);

    EXPECT_EQ(c.shape(), d.shape());
    EXPECT_EQ(c.strides(), d.strides());
    EXPECT_EQ(c.size(), d.size());
    EXPECT_EQ(c.buffer, d.buffer);
    
}






