/*
 Code by Drake Johnson

 Provides a template specialization of the 'println' class 
 for std::vector objects

 The following headers are included:
   - println.hpp : println
	 - <iostream> : cout
   - <vector>    : vector
*/
#ifndef CONS_PRINTLN_VECTOR_HEADER__
#define CONS_PRINTLN_VECTOR_HEADER__
#ifdef _MSC_VER
#	pragma once
#endif //_MSC_VER
#include "master.hpp"
#include <vector>

namespace cons
{
	template <class ValTy>
	/**
	 Template specialization for STL vector container. One element
	 is printed per line. For this method to compile, 'ValTy' must
	 be a printable type. The last object does not have a newline
	 character appended to it.

	 Example usage:
	 @code
		 cons::println v1(std::vector<std::string>
		 {
			 "Test 1",
			 "Test 2",
			 "Test 3"
		 });

		 std::vector<double> doubs
		 {
			 1.03485,
			 44.281 ,
			 55.0   ,
			 198.53
		 };
		 cons::println v2(doubs);
	 @endcode
	*/
	class println <std::vector<ValTy>>
	{
	public:
		println(const std::vector<ValTy>& lines)
		{
			for (const auto& line : lines)
			{
				println<decltype(line)> p(line);

				// Newline for all except last element
				if (static_cast<const void*>(&line) != 
					static_cast<const void*>(&lines.at(lines.size() - 1)))
					std::cout << '\n';
			}
		}
	};
} // namespace cons
#endif // !CONS_PRINTLN_VECTOR_HEADER__
