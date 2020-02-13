/*
 Code by Drake Johnson

 This header contains different functions for clearing the
 terminal on multiple operating systems. This includes
 Windows and Unix based systems.

 Header includes:
   - print.hpp : print()
     - println.hpp
     - <type_traits>
    
   - <windows.h> : HANDLE, CONSOLE_SCREEN_BUFFER_INFO, DWORD, COORD
   - <unistd.h>
   - <term.h>
*/
#ifndef CONS_CLEAR_SCREEN_HEADER__
#define CONS_CLEAR_SCREEN_HEADER__
#ifdef _MSC_VER
#	pragma once
#endif //_MSC_VER
#include <exception>
namespace cons
{
    void clear_screen();
    inline auto cls = clear_screen;
    
    // Exception for any errors during screen clearing
    struct ClearScreenException : std::exception
    {
        [[nodiscard]] const char* what() const override
        {
            return "\nERROR CLEARING SCREEN!";
        }
    };
} // namespace cons
#endif // !CONS_CLEAR_SCREEN_HEADER__