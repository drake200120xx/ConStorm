/*
 Code by Drake Johnson

 Contains an overload for the 'input' function that allows
 for user input to be validated to an element inside of an
 std::unordered_list (which can be initialized with braces).

 Header includes:
   - input_function.hpp
     - output/prompt.hpp : prompt()
       - println.hpp : println
         - println/master.hpp : <iostream>       : cin
         - println/set        : <unordered_set>  : unordered_set
         - println/vector
     - <functional>
     - <limits>          : numeric_limits
     - <string>          : string
*/
#ifndef CONS_INPUT_SET_HEADER__
#define CONS_INPUT_SET_HEADER__
#ifdef _MSC_VER
#	pragma once
#endif //_MSC_VER
#include "input_function.hpp"

namespace cons
{
    template <typename InTy>
    /**
     Gets valid input from the user. Valid input is based on `valid_set`,
     which is an unordered_set of valid inputs. If `valid_set` is empty,
     the 'input' function defined in 'input_function.hpp' is called and
     all inputs are accepted. std::cin is cleared up to a newline character
     before returning.

     Example usage:
     @code
         std::unordered_set<int> valids{ 1, 2, 3, 4 };
         const auto final_input = cons::input<int>(valids);

         const auto final_input2 = cons::input<int>({ 5, 6, 7, 8 });
     @endcode

     @param valid_set An set of valid inputs as specified above
     @param invalid_msg The message to display upon invalid input
     @returns The first valid input from the user
    */
    InTy input(
        std::unordered_set<InTy> valid_set, 
        const std::string& invalid_msg = "Invalid input. Re-enter: ")
    {
        InTy user_input;

        if (valid_set.empty())
            user_input = cons::input<InTy>();
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

                while (!(std::cin >> user_input))
                { // Handles invalid input types
                    prompt(invalid_msg);
                    std::cin.clear();
                    std::cin.ignore(CIN_MAX, '\n');
                }

            } while (valid_set.find(user_input) == valid_set.end());
        }

        if (std::cin.rdbuf()->in_avail() > 0)
        {
            std::cin.ignore(CIN_MAX, '\n');
            std::cin.clear();
        }

        return user_input;
    }

    template <>
    /**
     Template specialization of the above overload of 'input' for std::strings
     that uses std::getline instead of std::cin. In the case of an empty set,
     all inputs are accepted.

     @param valid_set An set of valid inputs as specified above
     @param invalid_msg The message to display upon invalid input
     @returns The first valid input from the user
    */
    std::string input<std::string>(
        std::unordered_set<std::string> valid_set,
        const std::string& invalid_msg);
} // namespace cons
#endif // !CONS_INPUT_SET_HEADER__
