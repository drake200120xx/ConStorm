/*
 Code by Drake Johnson
*/

#include "input/input_set.hpp"

namespace cons
{
	template <>
	std::string input<std::basic_string<char>>(
		std::unordered_set<std::string> valid_set, 
		const std::string& invalid_msg)
	{
		std::string user_input;

		if (valid_set.empty())
			user_input = cons::input<std::string>();
		else
		{
			bool first_loop = true;
			do
			{
				if (first_loop)
				{ // Suppress error msg on first iteration
					first_loop = false;
				}
				else
					prompt(invalid_msg);

				std::getline(std::cin, user_input);

			} while (valid_set.find(user_input) == valid_set.end());
		}

		return user_input;
	}
} // namespace cons
