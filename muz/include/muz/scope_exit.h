#pragma once

#include <algorithm>

template<typename FuncType>
class muzScopeExit
{
 public:
   explicit muzScopeExit(FuncType&& func)
     : func(std::move(func))
   {
   }

   muzScopeExit()
   {
      func();
   }

   muzScopeExit(const muzScopeExit&) = delete;
   muzScopeExit(muzScopeExit&&) = delete;

   muzScopeExit& operator=(const muzScopeExit&) = delete;
   muzScopeExit& operator=(muzScopeExit&&) = delete;

 private:
   FuncType func;
};
