/*
 Code by Drake Johnson

 Combines several IO functions to form the main event loop
 for the menu-driven system for console games. Also defines
 the Menu class.

 Header includes:
   - interface.hpp : MenuInterface

   - input.hpp
	 - input_function.hpp
	   - output/prompt.hpp
	   - <functional>
	   - <limits>
	   - <string>
	 - input_set.hpp
	 - pause.hpp
	   - output/print.hpp
	   - <type_traits>

   - output.hpp
	 - print.hpp
	 - prompt.hpp
	 - animate.hpp
	 - clear_screen.hpp
	 - header.hpp
*/
#ifndef CONS_MENU_MENU_HEADER__
#define CONS_MENU_MENU_HEADER__
#ifdef _MSC_VER
#	pragma once
#endif //_MSC_VER
#include "interface.hpp"
#include "output/header.hpp"
#include <utility>

namespace cons
{
	/**
	 The primary menu class. Displays a title, optional description, options,
	 and an input prompt. The options correspond to a MenuInterface*, which is
	 the following menu to go to after the run() method of this object is 
	 executed.
	 
	 @param m_title      The title to display at the top of the menu
	 @param m_desc       A description of the current menu to show under m_title
	 @param m_prompt_msg The message to prompt the user for input
	 @param m_options    The options to display to the user. Size must equal m_gotos
	 @param m_gotos      A MenuInterface* that corresponds to the option
	*/
	class Menu : public MenuInterface
	{
	public:
		using options_container = std::vector<std::string>;
		using menu_container = std::vector<MenuInterface*>;
		
		Menu();
		Menu(Header title);

		Menu(const Menu& other);
		Menu& operator=(const Menu& other);

		Menu(Menu&& other) noexcept;
		Menu& operator=(Menu&& other) noexcept;

		~Menu() = default;

		[[nodiscard]] const MenuInterface* run() const override;

		void set_title(Header title) { m_title = std::move(title); }
		void set_description(WordWrap desc) { m_desc = std::move(desc); }
		void set_description(std::string desc_text);
		void set_description(
			std::string desc_text,
			unsigned char_per_line,
			unsigned spaces_for_tab = 4U);

		void set_prompt_msg(std::string prompt_msg);
		void set_options(const options_container& options, const menu_container& gotos);
		void append_option(const std::string& option, MenuInterface* goto_menu);

		/**
		 @param index Index position to the text and 'goto' address of a given object
		 @returns A reference to the text of the option at 'index' and a pointer
		          to its 'goto' address
		*/
		auto operator[](const size_t index) 
		{ 
			return get_option_ptr(index); 
		}

		/**
		 @param index Index position to the text and 'goto' address of a given object
		 @returns The text of the option at 'index' and its 'goto' address
		*/
		auto operator[](const size_t index) const
		{
			return get_option(index);
		}

		[[nodiscard]] Header get_title() const { return m_title; }
		[[nodiscard]] WordWrap get_description() const { return m_desc; }

	private:
		Header m_title;
		WordWrap m_desc;
		std::string m_prompt_msg;
		options_container m_options;
		menu_container m_gotos;

		void display() const override;

		struct OptionPairPtr
		{
			std::string& text;
			MenuInterface*& goto_menu;
		};

		struct OptionPair
		{
			std::string text;
			MenuInterface* goto_menu;
		};

		OptionPairPtr get_option_ptr(const size_t index);
		OptionPair get_option(const size_t index) const;
	};
} // namespace cons
#endif // !CONS_MENU_MENU_HEADER__
