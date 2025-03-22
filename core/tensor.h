#pragma once

#include <memory>

#include "buffer.h"
#include "view.h"
#include "ops.h"

template <typename T>
struct Tensor {
    View view;
    std::shared_ptr<Buffer> buffer; 
};
