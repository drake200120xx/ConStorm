/*
 Code by Drake Johnson

 Defines the 'prompt' function, which prints one printable
 object and does not move to the next line

 Header includes:
   - println.hpp
     - println/master.hpp : println
     - println/set.hpp
     - println/vector.hpp

   - <type_traits> : forward, move
*/
#ifndef CONS_PROMPT_HEADER__
#define CONS_PROMPT_HEADER__
#ifdef _MSC_VER
#	pragma once
#endif //_MSC_VER
#include "println.hpp"
#include <type_traits>

namespace cons
{
    template <typename PrTy = const char*>
    /**
     A wrapper function for calling 'println' and displaying only
     one printable object without moving to a new line. Since 'println' is
     used to print the prompt message, any printable object may be used.

     This function may be called with no parameters for the default
     message "Enter: " to be displayed.

     @param prompt The prompt message to display to the user
    */
    void prompt(PrTy prompt = "Enter: ")
    {
        println<PrTy> p(std::forward<PrTy>(prompt));
        std::cout << std::flush;
    }

} // namespace cons
#endif // !CONS_PROMPT_HEADER__