/*
 Code by Drake Johnson

 The println class defines the behavior of all printable objects
 and which objects are printable.

 The following STL headers are included:
   - <iostream> : cout
*/
#ifndef CONS_PRINTLN_MASTER_HEADER__
#define CONS_PRINTLN_MASTER_HEADER__
#ifdef _MSC_VER
#	pragma once
#endif //_MSC_VER
#include <iostream>

namespace cons
{
	template <class LnTy, class = void>
	/**
	 Classes are used due to the current limitations that are function
	 partial template specialization. To overcome this, 'println' is
	 defined as a class, and, because of this, must have an object
	 created to call it.

	 NOTE: It is recommended not to use println directly and, instead
	       use functions like cons::print() or cons::prompt() to
		   call println correctly.

	 Example usage:
	 @code
		 cons::println p1("Test 1");
		 cons::println p2(std::string("Test 2"));
		 cons::println p3(3);
		 cons::println p4(-4.0f);
	 @endcode
	*/
	class println
	{
	public:
		println(LnTy line)
		{
			std::cout << line;
		}
	};

} // namespace cons
#endif // !CONS_PRINTLN_MASTER_HEADER__
