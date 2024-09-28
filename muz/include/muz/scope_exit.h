#pragma once

#include <algorithm>

namespace muz {

   template<typename FuncType>
   class ScopeExit
   {
    public:
      explicit ScopeExit(FuncType&& func)
        : func(std::move(func))
      {
      }

      ~ScopeExit()
      {
         func();
      }

      ScopeExit(const ScopeExit&) = delete;
      ScopeExit(ScopeExit&&) = delete;

      ScopeExit& operator=(const ScopeExit&) = delete;
      ScopeExit& operator=(ScopeExit&&) = delete;

    private:
      FuncType func;
   };

} // namespace muz

