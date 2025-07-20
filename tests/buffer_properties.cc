#include <gtest/gtest.h>

#include "../core/buffer.h"

TEST(BufferProperties, allocation_size) {
    Buffer<float> buffer1 {22};
    EXPECT_EQ(buffer1.data.size(), 22);

    Buffer<float> buffer2 {32};
    EXPECT_EQ(buffer2.data.size(), 32);

    Buffer<float> buffer3 {32};
    EXPECT_EQ(buffer3.data.size(), 32);

    Buffer<float> buffer4 {55};
    EXPECT_EQ(buffer4.data.size(), 55);
}

