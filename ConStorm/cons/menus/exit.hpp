/*
 Code by Drake Johnson

 Contains the ExitMenu class
*/
#ifdef _MSC_VER
#	pragma once
#endif // _MSC_VER
#ifndef CONS_MENU_EXIT_HEADER__
#define CONS_MENU_EXIT_HEADER__
#include "interface.hpp"
#include <string>
namespace cons
{
	/**
	 Optionally displays an exit message before returning nullptr

	 @param m_exit_msg Exit message (if empty string, no message is 
	                   given before exiting
	*/
	class ExitMenu final : public MenuInterface
	{
	public:
		ExitMenu(std::string exit_msg = "Press any key to exit...");

		[[nodiscard]] const MenuInterface* run() const override;

		void set_exit_msg(const std::string& msg) { m_exit_msg = msg; }

		[[nodiscard]] std::string get_exit_msg() const { return m_exit_msg; }

	private:
		std::string m_exit_msg;

		void display() const override {}
	};
} // namespace cons
#endif // CONS_MENU_EXIT_HEADER__