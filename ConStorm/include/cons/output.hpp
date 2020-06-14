/*
 Code by Drake Johnson

 The following header files are included from "cons/output/":
   - print.hpp
     - println.hpp
       - println/master.hpp
         - <iostream> : cout
       - println/set.hpp
         - println/master.hpp
         - <set>           : set
         - <unordered_set> : unordered_set
       - println/textf.hpp
         - println/master.hpp
         - <exception>   : exception
         - <string_view> : string_view
         - <windows.h>   : CONSOLE_SCREEN_BUFFER_INFO, COORD, HANDLE, WORD
       - println/vector.hpp
         - println/master.hpp
         - <vector> : vector
       - word_wrap.hpp
         - <string>        : string
         - <unordered_set> : unordered_set
         - <vector>        : vector

   - prompt.hpp
     - println.hpp
     - <type_traits> : forward, move

   - animate.hpp
     - println.hpp
     - <string> : string

   - clear_screen.hpp
     - print.hpp
     
   - header.hpp
     - textf.hpp : textf
*/
#ifdef _MSC_VER
#	pragma once
#endif //_MSC_VER
#ifndef CONS_OUTPUT_HEADER__
#define CONS_OUTPUT_HEADER__

#include "output/println.hpp"
#include "output/print.hpp"
#include "output/prompt.hpp"
#include "output/clear_screen.hpp"
#include "output/header.hpp"

#endif // !CONS_OUTPUT_HEADER__
