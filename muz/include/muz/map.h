#pragma once

#include <unordered_map>

template<class Kty, class Ty, class Hash = std::hash<Kty>, class KeyEq = std::equal_to<Kty>, class Alloc = std::allocator<std::pair<const Kty, Ty>>>
using muzMap [[maybe_unused]] = std::unordered_map<Kty, Ty, Hash, KeyEq, Alloc>;
