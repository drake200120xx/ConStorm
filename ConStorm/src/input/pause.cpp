/*
 Code by Drake Johnson
*/

#include "../../include/cons/input/pause.hpp"

namespace cons
{
	void pause(const std::string& msg)
	{
		print(msg);
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail() + 1);
	}
} // namespace cons