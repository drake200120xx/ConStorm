/*
 Code by Drake Johnson

 This header defines the print function. This function abstracts away direct 
 calls to the 'println' classes. 

 Included in this header:
   - println.hpp : <iostream> : cout, flush
   - <type_traits>            : std::forward 
*/
#ifndef CONS_PRINT_HEADER__
#define CONS_PRINT_HEADER__
#ifdef _MSC_VER
#	pragma once
#endif //_MSC_VER
#include "println.hpp"
#include <type_traits>

namespace cons
{
	/**
	 Empty overload for 'print' function that flushes the stream
	*/
	inline void print() { std::cout << std::flush; }

	template <typename LnTy, typename... OtherLnTy>
	/**
	 A wrapper function for calling the 'println' and displaying
	 one printable object per line.

	 @param line   The current line to be sent to 'println'
	 @param others The lines to be recursively sent back through the function
	*/
	void print(LnTy line, OtherLnTy... others)
	{
		{ // `p` will be deleted when exiting this scope to save memory
			println<LnTy> p(line);
		}
		std::cout << '\n';

		// Print `others` recursively
		print(std::forward<OtherLnTy>(others)...);
	}
} // namespace cons 
#endif // !CONS_PRINT_HEADER__
