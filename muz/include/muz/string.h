#pragma once

#ifdef MUZ_USE_STRINGZILLA
#include <stringzilla/stringzilla.hpp>
#else
#include <string>
#include <string_view>
#endif

namespace muz {

#ifdef MUZ_USE_STRINGZILLA
   using String = ashvardanian::stringzilla::string;
   using StringView = ashvardanian::stringzilla::string_view;
#else
   using String = std::string;
   using StringView = std::string_view;
#endif

} // namespace muz
