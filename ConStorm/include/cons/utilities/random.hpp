/*
 Code by Drake Johnson

 Contains the 'Random' class for random number generation
*/
#ifndef CONS_UTILITIES_RANDOM_HEADER__
#define CONS_UTILITIES_RANDOM_HEADER__
#include <random>
#ifdef min
#   undef min
#endif // min
#ifdef max
#   undef max
#endif // max

namespace cons
{
    /**
     A static class to handle random number generation by calling a static engine
     and casting it into different distributions.

     @param s_Engine_init Is 'true' when the engine has been seeded once
     @param s_Engine      The std::default_random_engine to use for number generation
    */
    class Random
    {
    public:
        Random() = delete;

        template <class NumTy>
        /**
         Returns a random whole number within the specified bounds

         @param lower The lower bound of the random number (inclusive)
         @param upper The upper bound of the random number (inclusive)
         @returns A random whole number within [lower, upper]
        */
        static NumTy number(
            const NumTy lower = std::numeric_limits<NumTy>::min(), 
            const NumTy upper = std::numeric_limits<NumTy>::max())
        {
            static_assert(std::is_integral_v<NumTy>, "Type must be integral");
            engine_init();

            std::uniform_int_distribution<NumTy> dist(lower, upper);
            return dist(s_Engine);
        }

        template <class DecTy>
        /**
         Returns a random floating point number within the specified bounds

         @param lower The lower bound of the random number (inclusive)
         @param upper the upper bound of the random number (inclusive)
         @returns A random floating point number within [lower, upper]
        */
        static DecTy decimal(
            const DecTy lower = std::numeric_limits<DecTy>::min(), 
            const DecTy upper = std::numeric_limits<DecTy>::max())
        {
            static_assert(std::is_floating_point_v<DecTy>, "Type must be floating point");
            engine_init();

            std::uniform_real_distribution<DecTy> dist(lower, upper);
            return dist(s_Engine);
        }

    private:
        inline static bool s_Engine_init = false;
        static std::default_random_engine s_Engine;

        static void engine_init();
    };
} // namespace cons
#endif // CONS_UTILITIES_RANDOM_HEADER__
