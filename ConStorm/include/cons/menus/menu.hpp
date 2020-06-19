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
#include "interface.hpp"
#include <cons/output/header.hpp>

namespace cons
{
	/**
	 The primary menu class. Displays a title, optional description, options,
	 and an input prompt. The options correspond to a MenuInterface*, which is
	 the following menu to go to after the run() method of this object is 
	 executed.
	 
	 @param title_      The title to display at the top of the menu
	 @param desc_       A description of the current menu to show under title_
	 @param prompt_msg_ The message to prompt the user for input
	 @param options_    The options to display to the user. Size must equal gotos_
	 @param gotos_      A MenuInterface* that corresponds to the option
	*/
	class Menu : public MenuInterface
	{
	protected:
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

	public:
		using options_container = std::vector<std::string>;
		using menu_container = std::vector<MenuInterface*>;
		
		Menu();
		Menu(Header title);
		Menu(const Menu& other);
		Menu(Menu&& other) noexcept;
		virtual ~Menu() = default;

		Menu& operator=(const Menu& other);
		Menu& operator=(Menu&& other) noexcept;

		[[nodiscard]] const MenuInterface* run() const override;

		void set_title(Header title);
		void set_description(WordWrap desc);
		void set_description(std::string desc_text);
		void set_description(std::string desc_text, unsigned char_per_line,
			unsigned spaces_for_tab = 4U);

		void set_prompt_msg(std::string prompt_msg);
		void set_options(options_container options, menu_container gotos);
		void append_option(const std::string& option, MenuInterface* goto_menu);

		/**
		 @param index Index position to the text and 'goto' address of a given object
		 @returns A reference to the text of the option at 'index' and a pointer
		          to its 'goto' address
		*/
		OptionPairPtr operator[](size_t index);

		/**
		 @param index Index position to the text and 'goto' address of a given object
		 @returns The text of the option at 'index' and its 'goto' address
		*/
		OptionPair operator[](size_t index) const;

		[[nodiscard]] Header get_title() const;
		[[nodiscard]] WordWrap get_description() const;

	protected:
		Header title_;
		WordWrap desc_;
		std::string prompt_msg_;
		options_container options_;
		menu_container gotos_;

		void display() const override;

		OptionPairPtr get_option_ptr(size_t index);
		OptionPair get_option(size_t index) const;

		static void copy(Menu& dest, const Menu& src);
		static void move(Menu& dest, Menu&& src) noexcept;
	};
} // namespace cons
#endif // !CONS_MENU_MENU_HEADER__
