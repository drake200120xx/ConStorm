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
#ifndef CONS_PRINTLN_DEQUE_HEADER__
#define CONS_PRINTLN_DEQUE_HEADER__
#include "master.hpp"
#include <deque>

namespace cons
{
    template <class ValTy>
    /**
     Template specialization for STL deque container. One element is printed per
     line. For this method to compile, 'ValTy' must be a printable type. The
     last object does not have a newline character appended to it.

     Example usage:
     @code
         cons::println(std::deque<std::string>
         {
             "Test 1",
             "Test 2",
             "Test 3"
         });
     @endcode
    */
    class println <std::deque<ValTy>>
    {
    public:
        println(std::deque<ValTy> lines)
        {
            size_t itr = 0;
            const auto lines_size = lines.size();
            for (const auto& line : lines)
            {
                println<decltype(line)> p(line);

                if (itr != lines_size - 1)
                    std::cout << '\n';
                itr++;
            }
        }
    };
} // namespace cons
#endif // CONS_PRINTLN_DEQUE_HEADER__
