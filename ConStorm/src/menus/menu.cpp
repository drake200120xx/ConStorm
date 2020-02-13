/*
 Code by Drake Johnson
*/

#include "menus/menu.hpp"
#include "output.hpp"
#include "input.hpp"

namespace cons
{
	struct menu_options_size_mismatch_exception : std::exception
	{
		[[nodiscard]] const char* what() const override
		{
			return "m_options and m_gotos must be the same size!";
		}
	};

	Menu::Menu()
		: m_desc("", 80, 4)
	{}

	Menu::Menu(Header title)
		: m_title(std::move(title))
		, m_desc("", 80, 4)
	{}

	Menu::Menu(const Menu& other)
		: m_title(other.m_title)
		, m_desc(other.m_desc)
		, m_prompt_msg(other.m_prompt_msg)
		, m_options(other.m_options)
		, m_gotos(other.m_gotos)
	{}

	Menu& Menu::operator=(const Menu& other)
	{
		if (this != &other)
		{
			m_title = other.m_title;
			m_desc = other.m_desc;
			m_prompt_msg = other.m_prompt_msg;
			m_options = other.m_options;
			m_gotos = other.m_gotos;
		}

		return *this;
	}

	Menu::Menu(Menu&& other) noexcept
		: m_title(std::move(other.m_title))
		, m_desc(std::move(other.m_desc))
		, m_prompt_msg(std::move(other.m_prompt_msg))
		, m_options(std::move(other.m_options))
		, m_gotos(std::move(other.m_gotos))
	{}

	Menu& Menu::operator=(Menu&& other) noexcept
	{
		if (this != &other)
		{
			m_title = std::move(other.m_title);
			m_desc = std::move(other.m_desc);
			m_prompt_msg = std::move(other.m_prompt_msg);
			m_options = std::move(other.m_options);
			m_gotos = std::move(other.m_gotos);
		}

		return *this;
	}

	const MenuInterface* Menu::run() const
	{
		display();

		const auto options_size = m_options.size();
		const auto user_input = input<unsigned>(
			[&options_size](size_t input) -> bool
			{
				return input > 0 && input <= options_size;
			}
		);

		return m_gotos.at(user_input - 1);
	}

	void Menu::set_description(std::string desc_text)
	{
		m_desc =
			WordWrap(
				std::move(desc_text),
				m_desc.getCharCount(),
				m_desc.getTabSpaces());
	}

	void Menu::set_description(
		std::string desc_text, 
		const unsigned char_per_line,
		const unsigned spaces_for_tab)
	{
		m_desc = WordWrap(
			std::move(desc_text),
			char_per_line,
			spaces_for_tab);
	}

	void Menu::set_prompt_msg(std::string prompt_msg)
	{
		m_prompt_msg = std::move(prompt_msg);
	}


	void Menu::set_options(const options_container& options, const menu_container& gotos)
	{
		try
		{
			if (options.size() != gotos.size())
				throw menu_options_size_mismatch_exception();

			m_options = options;
			m_gotos = gotos;
		}
		catch (const menu_options_size_mismatch_exception & err)
		{
			print(err.what());
		}
	}

	void Menu::append_option(const std::string& option, MenuInterface* goto_menu)
	{
		m_options.push_back(option);
		m_gotos.push_back(goto_menu);
	}

	void Menu::display() const
	{
		cls();

		print(
			m_title,
			m_desc,
			""
		);

		for (size_t i = 0; i < m_options.size(); ++i)
		{
			std::cout
				<< " (" << (i + 1) << ") "
				<< m_options.at(i) << '\n';
		}
		std::cout << std::endl;

		if (m_prompt_msg.empty())
			prompt();
		else
			prompt(m_prompt_msg);
	}

	Menu::OptionPairPtr Menu::get_option_ptr(const size_t index)
	{
		return { m_options.at(index), m_gotos.at(index) };
	}

	Menu::OptionPair Menu::get_option(const size_t index) const
	{
		return { m_options.at(index), m_gotos.at(index) };
	}
} // namespace cons
