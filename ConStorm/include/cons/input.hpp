/*
 Code by Drake Johnson

 The following header files are included from "cons\input\"
   - input_function.hpp
     - output/prompt.hpp
       - output/println.hpp
         - output/println/master
           - <iostream>
         - output/println/set
           - output/println/master
           - <set>
           - <unordered_set>
         - output/println/vector
           - output/println/master
           - <vector>
     - <functional>
     - <limits>
     - <string>

   - input_set.hpp
     - input_function.hpp

   - pause.hpp
     - output/print.hpp
       - output/println.hpp
       - <type_traits>
*/
#ifdef _MSC_VER
#	pragma once
#endif //_MSC_VER
#ifndef CONS_INPUT_HEADER__
#define CONS_INPUT_HEADER__

#include "input/input_function.hpp"
#include "input/input_set.hpp"
#include "input/pause.hpp"

#endif // !CONS_INPUT_HEADER__
