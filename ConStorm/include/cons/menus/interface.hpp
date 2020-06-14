/*
 Code by Drake Johnson

 Contains the interface for all menu classes
*/
#ifndef CONS_MENU_INTERFACE_HEADER__
#define CONS_MENU_INTERFACE_HEADER__
#ifdef _MSC_VER
#   pragma once
#endif // _MSC_VER
namespace cons
{
    /**
     The MenuInterface interface is very useful if none of the already made
     implementations of this class suit a given need. In that case, simply
     implement this method.
    */
    class MenuInterface
    {
    public:
        virtual ~MenuInterface() = default;

        /**
         This method gets called inside the loop of cons::menu_loop(). Whatever
         MenuInterface* it returns will be a pointer to the next object from
         which to call the 'run()' method. This loop continues until a nullptr
         is returned.

         @returns A pointer to the next object to call the 'run()' method from
        */
        [[nodiscard]] virtual const MenuInterface* run() const = 0;

    protected:
        MenuInterface()                                    = default;
        MenuInterface(const MenuInterface&)                = default;
        MenuInterface(MenuInterface&&) noexcept            = default;
        MenuInterface& operator=(const MenuInterface&)     = default;
        MenuInterface& operator=(MenuInterface&&) noexcept = default;

        /**
         This method is essentially optional to organize code. All display code
         can easily go inside the 'run()' method. However, to keep the
         functionality of the 'run()' method obvious, it is recommended to put
         all output code in this method. A call to this method is usually the
         first line of code in the 'run()' method.
        */
        virtual void display() const = 0;
    };
} // namespace cons
#endif // CONS_MENU_INTERFACE_HEADER__
