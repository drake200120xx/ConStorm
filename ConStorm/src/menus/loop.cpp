/*
 Code by Drake Johnson
*/

#include "menus/loop.hpp"

namespace cons
{
	void menu_loop(const MenuInterface* const start_menu)
	{
		auto next_menu = start_menu;
		while (next_menu != nullptr)
			next_menu = next_menu->run();
	}
} // namespace cons
