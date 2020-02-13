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
    class MenuInterface
    {
    public:
        virtual ~MenuInterface() = default;
        [[nodiscard]] virtual const MenuInterface* run() const = 0;

    protected:
        virtual void display() const = 0;
    };
} // namespace cons
#endif // CONS_MENU_INTERFACE_HEADER__
