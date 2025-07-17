#include <gtest/gtest.h>
#include <new>
#include "../core/buffer.h"

void buffer_allocation_to_throw() {
    Buffer<float> buffer {0};
}

TEST(BufferProperties, alignment) {
    EXPECT_THROW(buffer_allocation_to_throw(), std::bad_array_new_length);
    // EXPECT_ANY_THROW(buffer_allocation_to_throw());

    Buffer<float> buffer1 {22};
    EXPECT_EQ(buffer1.size, 22);
    EXPECT_EQ(buffer1.capacity, 32);

    Buffer<float> buffer2 {32};
    EXPECT_EQ(buffer2.size, 32);
    EXPECT_EQ(buffer2.capacity, 32);

    Buffer<float> buffer3 {32};
    EXPECT_EQ(buffer3.size, 32);
    EXPECT_EQ(buffer3.capacity, 32);

    Buffer<float> buffer4 {55};
    EXPECT_EQ(buffer4.size, 55);
    EXPECT_EQ(buffer4.capacity, 64);
}

