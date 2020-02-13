/*
 Code by Drake Johnson

 Includes all the headers in "cons/output/println/"

 Headers included:
   - master.hpp
     - <iostream> : cout

   - set.hpp
     - master.hpp
     - <set>           : set
     - <unordered_set> : unordered_set

   - vector.hpp
     - master.hpp
     - <vector> : vector

   - textf.hpp
     - master.hpp
       - <iostream> : cout
     - <exception>   : exception
     - <string_view> : string_view
     - <Windows.h>

   - word_wrap.hpp
     - <string>        : string
     - <string_view>   : string_view
     - <unordered_set> : unordered_set
     - <vector>        : vector
*/
#ifdef _MSC_VER
#	pragma once
#endif //_MSC_VER
#ifndef CONS_PRINTLN_HEADER__
#define CONS_PRINTLN_HEADER__

#include "println/master.hpp"
#include "println/set.hpp"
#include "println/vector.hpp"
#include "println/textf.hpp"
#include "word_wrap.hpp"

#endif // !CONS_PRINTLN_HEADER__
