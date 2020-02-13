/*
 Code by Drake Johnson
*/

#include "input/input_function.hpp"

namespace cons
{
	template <>
	std::string input<std::basic_string<char>>(
		std::function<bool(std::string)> valid_func, 
		const std::string& invalid_msg)
	{
		std::string user_input;

		bool first_loop = true;
		do
		{
			if (first_loop)
			{ // Suppresses error msg on loop's first iteration
				first_loop = false;
			}
			else
			{ // Error msg for invalid input.
				prompt(invalid_msg);
			}

			std::getline(std::cin, user_input);

		} while (!valid_func(user_input));

		return user_input;
	}
} // namespace cons
