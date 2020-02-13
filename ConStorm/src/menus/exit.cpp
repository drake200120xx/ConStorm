/*
 Code by Drake Johnson
*/

#include "menus/exit.hpp"
#include "input/pause.hpp"

namespace cons
{
	ExitMenu::ExitMenu(std::string exit_msg)
		: m_exit_msg(std::move(exit_msg))
	{}

	const MenuInterface* ExitMenu::run() const
	{
		if (!m_exit_msg.empty())
			pause("\n " + m_exit_msg);
		return nullptr;
	}
} // namespace cons