/*
 Code by Drake Johnson

 Contains all headers in the 'function' folder
*/
#ifndef CONS_MENUS_FUNCTION_HEADER__
#define CONS_MENUS_FUNCTION_HEADER__
#ifdef _MSC_VER
#   pragma once
#endif // _MSC_VER
#include "function/default.hpp"
#include "function/no_params.hpp"
#include "function/void_params.hpp"

namespace cons
{
	template<class ReturnTy, class... ParamTypes>
	/**
	 Creates a menu with no output that simply evaluates a function and stores
	 the output in value_. There are three template specializations for this
	 class. The first is any return type with no parameters, the second is
	 a void return type with parameters, and the third is a void return type
	 with no parameters.

	 For a void return type, the template type must be specifically called. For
	 example,
	 @code
	 FuncMenu_base<void> no_return_params(1, 2, 3, 4);
	 FuncMenu_base<void> no_return_no_params;
	 @endcode

	 NOTE: In order to use the 'run()' method for any of these classes, set_function()
		   must first be called. More specifically, the boolean 'func_set_' must be
		   true. Otherwise, 'run()' will no execute and, instead, immediately return a
		   nullptr.

	 Example usage:
	 @code
	 const int p1 = 0, p2 = 1, p3 = 2;
	 const int default = -1;

	 FuncMenu_base f1(default, p1, p2, p3);
	 f1.set_function(
		[](int a1, int a2, int a3) -> int
		{
			return a1 + a2 + a3;
		}
	 );
	 auto next_menu1 = f1.run();

	 FuncMenu_base<void> f2(p1, p2, p3);
	 f2.set_function(
		[](int a1, int a2, int a3) -> void
		{
			cons::print(a1 + a2 + a3);
		}
	 );
	 auto next_menu2 = f2.run();
	 @endcode

	 @param func_set_   Whether m_function has been set to a usable function
	 @param m_funciton  The function to execute when 'run()' is called
	 @param m_args      A tuple of arguments to pass to m_function when 'run()' is called
	 @param m_value     The value returned from 'std::apply(m_function, m_args)'
	 @param m_goto_next A MenuInterface* to return from 'run()'
	*/
	using FunctionMenu = FuncMenu_base<ReturnTy, std::is_same_v<void, ReturnTy>, ParamTypes...>;
} // namespace cons
#endif // !CONS_MENUS_FUNCTION_HEADER__
