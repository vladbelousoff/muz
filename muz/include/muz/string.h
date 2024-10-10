#pragma once

#ifdef MUZ_USE_STRINGZILLA
#include <stringzilla/stringzilla.hpp>
#else
#include <string>
#include <string_view>
#endif

#ifdef MUZ_USE_STRINGZILLA
using muzString = ashvardanian::stringzilla::string;
using muzStringView = ashvardanian::stringzilla::string_view;
#else
using muzString = std::string;
using muzStringView = std::string_view;
#endif
