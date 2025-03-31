#pragma once

#include <type_traits>

template <typename T>
concept numeric_type = std::is_arithmetic_v<T>;

template <typename T, typename... Ts>
concept all_same_type = (std::is_same_v<T, Ts> && ...);

