#pragma once

#include <algorithm>

/**
 * @brief A helper class that guarantees a function is executed when the scope exits.
 *
 * This class takes a callable object (a function, lambda, etc.) as a parameter and ensures
 * that it is executed when the object goes out of scope. This is useful for performing
 * cleanup operations or ensuring that resources are released at the end of a scope.
 *
 * @tparam FunctionType The type of the callable object.
 */
template<typename FunctionType>
class muzScopeExit
{
 public:
   explicit muzScopeExit(FunctionType&& function)
     : function(std::forward<FunctionType>(function))
   {
   }

   ~muzScopeExit()
   {
      function();
   }

   muzScopeExit(const muzScopeExit&) = delete;
   muzScopeExit(muzScopeExit&&) = delete;

   muzScopeExit& operator=(const muzScopeExit&) = delete;
   muzScopeExit& operator=(muzScopeExit&&) = delete;

 private:
   FunctionType function;
};
