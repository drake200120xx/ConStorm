/*
 Code by Drake Johnson

 Contains the InputMenu class
*/
#ifndef CONS_MENU_INPUT_HEADER__
#define CONS_MENU_INPUT_HEADER__
#ifdef _MSC_VER
#   pragma once
#endif // _MSC_VER
#include "interface.hpp"
#include "../output.hpp"
#include "../input.hpp"

namespace cons
{
	template<class, class = void>
	class InputMenu;

	template<class ReturnTy>
	/**
	 Displays a title, description, and prompt. Collects stores input into a 
	 variable of type 'ReturnTy' that can be retrieved through 'get_value()'

	 @param m_title      The title of the menu; displayed at the top of the menu
	 @param m_desc       A section of text right under m_title
	 @param m_prompt_msg The message to prompt the user for input
	 @param m_validation The validation function to validate user input. Must take
						 in one parameter of type 'ReturnTy' and return a bool if
						 the input is valid or not
	 @param m_value      Validated user input from the most recent invocation of
						 'run()'
	*/
	class InputMenu<ReturnTy, std::enable_if_t<std::is_constructible_v<ReturnTy>>> : public MenuInterface
	{
	public:
		using value_type = ReturnTy;

		InputMenu()
			: InputMenu("")
		{}

		InputMenu(Header title)
			: m_title(std::move(title))
			, m_desc("", 80U, 4U)
			, m_validation([](value_type dummy) -> bool { return true; })
			, m_goto_next(nullptr)
		{}

		InputMenu(std::function<bool(value_type)> validation_function)
			: m_desc("", 80U, 4U)
			, m_validation(std::move(validation_function))
			, m_goto_next(nullptr)
		{}

		InputMenu(
			Header title, 
			std::function<bool(value_type)> validation_function)
			: m_title(std::move(title))
			, m_desc("", 80U, 4U)
			, m_validation(std::move(validation_function))
			, m_value()
			, m_goto_next(nullptr)
		{}

		InputMenu(const InputMenu& other)
			: m_title(other.m_title)
			, m_desc(other.m_desc)
			, m_prompt_msg(other.m_prompt_msg)
			, m_validation(other.m_validation)
			, m_value(other.m_value)
			, m_goto_next(other.m_goto_next)
		{}


		InputMenu& operator=(const InputMenu& other)
		{
			if (this != &other)
			{
				m_title = other.m_title;
				m_desc = other.m_desc;
				m_prompt_msg = other.m_prompt_msg;
				m_validation = other.m_validation;
				m_value = other.m_value;
				m_goto_next = other.m_goto_next;
			}

			return *this;
		}

		InputMenu(InputMenu&& other) noexcept
			: m_title(std::move(other.m_title))
			, m_desc(std::move(other.m_desc))
			, m_prompt_msg(std::move(other.m_prompt_msg))
			, m_validation(std::move(other.m_validation))
			, m_value(other.m_value)
			, m_goto_next(other.m_goto_next)
		{}

		InputMenu& operator=(InputMenu&& other) noexcept
		{
			if (this != &other)
			{
				m_title = std::move(other.m_title);
				m_desc = std::move(other.m_desc);
				m_prompt_msg = std::move(other.m_prompt_msg);
				m_validation = std::move(other.m_validation);
				m_value = other.m_value;
				m_goto_next = other.m_goto_next;
			}

			return *this;
		}

		~InputMenu() = default;

		[[nodiscard]] const MenuInterface* run() const override
		{
			display();

			m_value = input<value_type>(m_validation);
			return m_goto_next;
		}

		void set_title(const Header& title) { m_title = title; }
		void set_description(const WordWrap& desc) { m_desc = desc; }
		void set_description(const std::string& text) { m_desc = text; }
		void set_description(
			const std::string& text,
			const unsigned char_count,
			const unsigned space_for_tab = 4U)
		{
			m_desc = WordWrap(text, char_count, space_for_tab);
		}
		void set_prompt_msg(const std::string& prompt_msg) { m_prompt_msg = prompt_msg; }
		void set_validation(const std::function<bool(value_type)>& validation_function) 
		{ 
			m_validation = validation_function; 
		}
		void set_goto_next(MenuInterface* const menu_interface) { m_goto_next = menu_interface; }

		[[nodiscard]] Header get_title() const { return m_title; }
		[[nodiscard]] WordWrap get_desc() const { return m_desc; }
		[[nodiscard]] std::string get_prompt_msg() const { return m_prompt_msg; }
		[[nodiscard]] std::function<bool(value_type)> get_validation() const { return m_validation; }
		[[nodiscard]] value_type get_value() const { return m_value; }
		[[nodiscard]] MenuInterface* get_goto_next() const { return m_goto_next; }

	private:
		Header m_title;
		WordWrap m_desc;
		std::string m_prompt_msg;
		std::function<bool(value_type)> m_validation;
		mutable value_type m_value;
		MenuInterface* m_goto_next;

		void display() const override
		{
			cls();
			print(
				m_title,
				m_desc,
				""
			);
			if (m_prompt_msg.empty())
				prompt();
			else
				prompt(m_prompt_msg);
		}
	};
} // namespace cons
#endif // !CONS_MENU_INPUT_HEADER__
