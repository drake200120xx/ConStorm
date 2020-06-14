/*
 Code by Drake Johnson
*/
#include <cons/output/println/textf.hpp>

namespace cons
{
	textf::textf(std::string text)
		: text_(std::move(text))
		, color_(ConsoleColor::color::bright_white, ConsoleColor::color::black)
	{}

	textf::textf(const textf& other)
		: color_(ConsoleColor::color::bright_white, ConsoleColor::color::black)
	{
		copy(*this, other);
	}

	textf::textf(textf&& other) noexcept
		: color_(ConsoleColor::color::bright_white, ConsoleColor::color::black)
	{
		move(*this, std::move(other));
	}

	textf& textf::operator=(const textf& other)
	{
		if (this != &other)
			copy(*this, other);
		return *this;
	}

	textf& textf::operator=(textf&& other) noexcept
	{
		if (this != &other)
			move(*this, std::move(other));
		return *this;
	}

	void textf::display() const
	{
		const auto old_attribs = setup_console();
		std::cout << std::flush << text_;
		restore_console(old_attribs);
	}

	void textf::modify_color(const layer layer, const ConsoleColor color)
	{
		WORD new_win_color;
		auto win_fg = static_cast<WORD>(color.get_foreground_color());
		auto win_bg = static_cast<WORD>(color.get_background_color()) * 16;

		switch (layer)
		{
		case layer::foreground:
			new_win_color = static_cast<WORD>(color.get_foreground_color());
			win_fg |= new_win_color;
			color_.set_foreground_color(static_cast<ConsoleColor::color>(win_fg));
			break;

		case layer::background:
			new_win_color = static_cast<WORD>(color.get_background_color()) * 16;
			win_bg |= new_win_color;
			color_.set_background_color(static_cast<ConsoleColor::color>(win_bg));
			break;

		default:
			throw InvalidConsoleLayerEnumValueException();
		}
	}

	void textf::reset_color()
	{
		color_.set_foreground_color(ConsoleColor::color::bright_white);
		color_.set_background_color(ConsoleColor::color::black);
	}

	void textf::set_text(std::string text)
	{
		text_ = std::move(text);
	}

	void textf::set_color(const ConsoleColor color)
	{
		color_ = color;
	}

	void textf::set_foreground_color(const ConsoleColor::color color)
	{
		color_.set_foreground_color(color);
	}

	void textf::set_background_color(const ConsoleColor::color color)
	{
		color_.set_background_color(color);
	}

	std::string textf::get_text() const
	{
		return text_;
	}

	ConsoleColor textf::get_color() const
	{
		return color_;
	}

	textf& textf::operator=(std::string str)
	{
		text_ = std::move(str);
		return *this;
	}

	WORD textf::get_win_color(const ConsoleColor color)
	{
		return static_cast<WORD>(color.get_foreground_color()) + 16 * 
			static_cast<WORD>(color.get_background_color());
	}

	WORD textf::setup_console() const
	{
		HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		WORD old_attrib = -1;

		// Get console info
		if (!GetConsoleScreenBufferInfo(hout, &csbi))
			throw WindowsConsoleFailureException();

		// Save old colors
		old_attrib = csbi.wAttributes;

		// Set new color
		if (!SetConsoleTextAttribute(hout, get_win_color(color_)))
			throw WindowsConsoleFailureException();

		return old_attrib;
	}

	void textf::restore_console(const WORD old_attribs) const
	{
		try
		{
			// Set color back
			if (!SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
				old_attribs))
				throw WindowsConsoleFailureException();
		}
		catch (const WindowsConsoleFailureException& e)
		{
			println<decltype(e.what())> p(e.what());
		}
	}

	void textf::copy(textf& dest, const textf& src) 
	{
		dest.text_ = src.text_;
		dest.color_ = src.color_;
	}

	void textf::move(textf& dest, textf&& src) noexcept
	{
		dest.text_ = std::move(src.text_);
		dest.color_ = src.color_;
	}

	InvalidConsoleLayerEnumValueException::InvalidConsoleLayerEnumValueException()
		: InvalidConsoleEnumValueException("textf::layer")
	{}
} // namespace cons
