/*
 Code by Drake Johnson

 Provides a template specialization of the 'println' class
 for std::set and std::unordered_set objects

 The following headers are included:
   - println.hpp     : println
	 - <iostream> : cout
   - <set>           : set
   - <unordered_set> : unordered_set
*/
#ifndef CONS_PRINTLN_SET_HEADER__
#define CONS_PRINTLN_SET_HEADER__
#ifdef _MSC_VER
#	pragma once
#endif //_MSC_VER
#include "master.hpp"
#include <set>
#include <unordered_set>

namespace cons
{
	template <class ValTy>
	/**
	 Template specialization for STL set container. One element is printed per 
	 line. For this method to compile, 'ValTy' must be a printable type. The 
	 last object does not have a newline character appended to it.

	 Example usage:
	 @code 
		 cons::println(std::set<std::string>
		 {
			 "Test 1",
			 "Test 2",
			 "Test 3"
		 });
	 @endcode
	*/
	class println <std::set<ValTy>>
	{
	public:
		println(std::set<ValTy> lines)
		{
			for (auto itr = lines.begin(); itr != lines.end(); ++itr)
			{
				println<decltype(*itr)> p(*itr);

				if (itr != --lines.end())
					std::cout << '\n';
			}
		}
	};

	template <class ValTy>
	/**
	 Template specialization for STL unordered_set container. One element is 
	 printed per line. For this method to compile, 'ValTy' must be a printable 
	 type. The last object does not have a newline character appended to it.

	 Example usage:
	 @code
		 std::unordered_set<double> doubs
		 {
			 1.03485,
			 44.281 ,
			 55.0   ,
			 198.53
		 };
		 cons::println s2(doubs);
	 @endcode
	*/
	class println <std::unordered_set<ValTy>>
	{
	private:
		using itr = typename std::unordered_set<ValTy>::iterator;

	public:
		println(std::unordered_set<ValTy> lines)
		{
			const auto lines_size = lines.size();

			for (
				struct { size_t pos; itr val; } s {0, lines.begin()}; 
				s.val != lines.end();
				++s.pos, ++s.val)
			{
				println<decltype(*s.val)> p(*s.val);

				if (s.pos != lines_size - 1)
					std::cout << '\n';
			}
		}
	};
} // namespace cons
#endif // !CONS_PRINTLN_SET_HEADER__
