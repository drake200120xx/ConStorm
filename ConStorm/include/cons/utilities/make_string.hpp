/*
 Code by Drake Johnson

 Defines a function to recursively build an std::string
*/
#ifndef CONS_UTILITIES_MAKE_STRING_HEADER__
#define CONS_UTILITIES_MAKE_STRING_HEADER__
#include <sstream>

namespace cons
{
    /**
     Overload of cons::make_str() for no parameter. See the below method for
     further documentation

     @returns An empty string
    */
    inline const char* make_str()
    {
        return "";
    }

    template<class CurTy, class... OtherTys>
    /**
     Recursively builds an std::string from the function's arguments. Argument
     types must have an overloaded '<<' operator or this method will fail.

     @param cur_obj    The current object being added to the string
     @param other_objs The other objects that will be added to the string
     @returns A concatenated std::string of all argument values
    */
    std::string make_str(CurTy cur_obj, OtherTys... other_objs)
    {
        std::stringstream ss;
        ss << cur_obj << make_str(std::forward<OtherTys>(other_objs)...);
        return ss.str();
    }
} // namespace cons
#endif // CONS_UTILITIES_MAKE_STRING_HEADER__