/*
 Code by Drake Johnson
*/

#include <cons/menus/menu.hpp>
#include <cons/output.hpp>
#include <cons/input.hpp>

namespace cons
{
	struct menu_options_size_mismatch_exception : std::exception
	{
		[[nodiscard]] const char* what() const override
		{
			return "options_ and gotos_ must be the same size!";
		}
	};

	Menu::Menu()
		: desc_("", 80, 4)
	{}

	Menu::Menu(Header title)
		: title_(std::move(title))
		, desc_("", 80, 4)
	{}

	Menu::Menu(const Menu& other)
		: Menu()
	{
		copy(*this, other);
	}

	Menu::Menu(Menu&& other) noexcept
		: Menu()
	{
		move(*this, std::move(other));
	}

	Menu& Menu::operator=(const Menu& other)
	{
		if (this != &other)
			copy(*this, other);

		return *this;
	}

	Menu& Menu::operator=(Menu&& other) noexcept
	{
		if (this != &other)
			move(*this, std::move(other));

		return *this;
	}

	const MenuInterface* Menu::run() const
	{
		display();

		const auto options_size = options_.size();
		const auto user_input = input<unsigned>(
			[&options_size](size_t input) -> bool
			{
				return input > 0 && input <= options_size;
			}
		);

		return gotos_.at(user_input - 1);
	}

	void Menu::set_title(Header title)
	{
		title_ = std::move(title);
	}

	void Menu::set_description(WordWrap desc)
	{
		desc_ = std::move(desc);
	}

	void Menu::set_description(std::string desc_text)
	{
		desc_ = WordWrap(std::move(desc_text), desc_.get_char_count(),
				desc_.get_tab_spaces()
		);
	}

	void Menu::set_description(std::string desc_text, 
		const unsigned char_per_line, const unsigned spaces_for_tab)
	{
		desc_ = WordWrap(std::move(desc_text), char_per_line, spaces_for_tab);
	}

	void Menu::set_prompt_msg(std::string prompt_msg)
	{
		prompt_msg_ = std::move(prompt_msg);
	}


	void Menu::set_options(options_container options, menu_container gotos)
	{
		try
		{
			if (options.size() != gotos.size())
				throw menu_options_size_mismatch_exception();

			options_ = std::move(options);
			gotos_ = std::move(gotos);
		}
		catch (const menu_options_size_mismatch_exception& err)
		{
			print(err.what());
		}
	}

	void Menu::append_option(const std::string& option, MenuInterface* goto_menu)
	{
		options_.push_back(option);
		gotos_.push_back(goto_menu);
	}

	Menu::OptionPairPtr Menu::operator[](const size_t index)
	{
		return get_option_ptr(index);
	}

	Menu::OptionPair Menu::operator[](const size_t index) const
	{
		return get_option(index);
	}

	Header Menu::get_title() const
	{
		return title_;
	}

	WordWrap Menu::get_description() const
	{
		return desc_;
	}

	void Menu::display() const
	{
		cls();

		print(
			title_,
			desc_,
			""
		);

		for (size_t i = 0; i < options_.size(); ++i)
		{
			std::cout
				<< " (" << (i + 1) << ") "
				<< options_.at(i) << '\n';
		}
		std::cout << std::endl;

		if (prompt_msg_.empty())
			prompt();
		else
			prompt(prompt_msg_);
	}

	Menu::OptionPairPtr Menu::get_option_ptr(const size_t index)
	{
		return { options_.at(index), gotos_.at(index) };
	}

	Menu::OptionPair Menu::get_option(const size_t index) const
	{
		return { options_.at(index), gotos_.at(index) };
	}

	void Menu::copy(Menu& dest, const Menu& src)
	{
		dest.title_ = src.title_;
		dest.desc_ = src.desc_;
		dest.prompt_msg_ = src.prompt_msg_;
		dest.options_ = src.options_;
		dest.gotos_ = src.gotos_;
	}

	void Menu::move(Menu& dest, Menu&& src) noexcept
	{
		dest.title_ = std::move(src.title_);
		dest.desc_ = std::move(src.desc_);
		dest.prompt_msg_ = std::move(src.prompt_msg_);
		dest.options_ = std::move(src.options_);
		dest.gotos_ = std::move(src.gotos_);
	}

} // namespace cons
