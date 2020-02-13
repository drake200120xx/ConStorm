/*
 Code by Drake Johnson

 This header contains a pause function that pauses the
 console until the the user presses a key.

 Header includes:
   - output/print.hpp : print()
	 - output/println.hpp
	 - <type_traits>
*/
#ifndef CONS_PAUSE_HEADER__
#define CONS_PAUSE_HEADER__
#ifdef _MSC_VER
#	pragma once
#endif //_MSC_VER
#include "../output/print.hpp"
namespace cons
{
	/**
	 Pause the current thread and waits for user to press a key to continue

	 @param msg The prompt to display to the user to continue past the pause
	*/
	void pause(const std::string& msg = "Press any key to continue...");
} // namespace cons
#endif // !CONS_PAUSE_HEADER__
