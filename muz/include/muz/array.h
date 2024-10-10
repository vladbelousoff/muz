#pragma once

#include <array>
#include <vector>

template<class T, class Alloc = std::allocator<T>>
using muzDynArray [[maybe_unused]] = std::vector<T, Alloc>;

template<class T, std::size_t Size>
using muzFixArray [[maybe_unused]] = std::array<T, Size>;
