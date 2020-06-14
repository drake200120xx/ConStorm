/*
 Code by Drake Johnson

 Contains the 'input' function, which returns the first valid
 input from a user. User input is ran through a validation
 function and, if the input is valid, the function returns
 that input.

 This header includes:
   - output/prompt.hpp : prompt()
     - println.hpp
       - println/master.hpp : <iostream> : cin
       - println/set
       - println/vector
     - <type_traits> 
 
   - <functional> : function
   - <limits>     : numeric_limits
   - <string>     : string
*/
#ifdef _MSC_VER
#	pragma once
#endif //_MSC_VER
#ifndef CONS_INPUT_FUNCTION_HEADER__
#define CONS_INPUT_FUNCTION_HEADER__
#include "../output/prompt.hpp"
#include <functional>
#include <limits>
#include <string>

// Undefine min/max macros if applicable
#ifdef max
#   undef max
#endif // max
#ifdef min
#   undef min
#endif // min

namespace cons
{
    constexpr auto CIN_MAX = std::numeric_limits<std::streamsize>::max();

    template <typename InTy>
    /**
     Returns validated input from the user based on the passed
     validation function, which may be either a lambda, std::function, or a function
     pointer. No function may be specified; the default parameter is a lambda that
     unconditionally returns true.
     
     This function will clear the characters in std::cin's buffer up to a 
     newline character before returning.

     Note that the passed validation function MUST take in one
     parameter of type 'InTy' and return a boolean value. This function
     will have the user's input passed through it and return whether
     it is valid or not.

     Example usage:
     { // Begin code
         constexpr unsigned lower_bound = 5, upper_bound = 15;
         auto valid_func = [lower_bound, upper_bound](unsigned given_input) -> bool
         {
             return (input >= lower_bound) && (input <= upper_bound)
         };

         const auto final_input = cons::input<unsigned>(valid_func);
     } // End code

     @param valid_func The validation function specified above
     @param invalid_msg The message to display upon invalid input
     @returns The first valid input from the user
    */
    InTy input(
        std::function<bool(InTy)> valid_func = [](InTy dummy) -> bool { return true; }, 
        const std::string& invalid_msg       = "Invalid input. Re-enter: ")
    {
        InTy user_input;

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

            while (!(std::cin >> user_input))
            { // Validation loop for handling invalid input types
                prompt(invalid_msg);

                std::cin.clear();
                std::cin.ignore(CIN_MAX, '\n');
            }

        } while (!valid_func(user_input));

        if (std::cin.rdbuf()->in_avail() > 0)
        { // Clear remaining characters in std::cin, up to newline
            std::cin.ignore(CIN_MAX, '\n');
            std::cin.clear();
        }

        return user_input;
    }

    template <>
    /**
     Template specialization of 'input' for strings that uses std::getline
     instead of std::cin
     @see cons::input()

     @param valid_func The validation function specified above
     @param invalid_msg The message to display upon invalid input
     @returns The first valid input from the user
    */
    std::string input<std::string>(
        std::function<bool(std::string)> valid_func,
        const std::string& invalid_msg);

} // namespace cons
#endif // !CONS_INPUT_FUNCTION_HEADER__
