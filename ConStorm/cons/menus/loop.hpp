/*
 Code by Drake Johnson

 Contains the main loop for the menu system.
*/
#ifndef CONS_MENU_LOOP_HEADER__
#define CONS_MENU_LOOP_HEADER__
#ifdef _MSC_VER
#	pragma once
#endif // !_MSC_VER
#include "interface.hpp"
namespace cons
{
	/**
	 The main application loop for a menu-based application. All menus should, in
	 most cases, be created BEFORE this function is called. This loop will exit 
	 when the 'run()' method of a menu returns nullptr.

	 @param start_menu The first menu to call to start the application loop
	*/
	void menu_loop(const MenuInterface* start_menu);

} // namespace cons
#endif // !CONS_MENU_LOOP_HEADER__
