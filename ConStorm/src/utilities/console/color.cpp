/*
 Code by Drake Johnson

 Defines the ConsoleColor class
*/
#include <cons/utilities/console/color.hpp>

namespace cons
{
	ConsoleColor::ConsoleColor()
		: ConsoleColor(color::bright_white, color::black)
	{
		HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		// Get console info
		if (!GetConsoleScreenBufferInfo(hout, &csbi))
			throw WindowsConsoleFailureException();

		// [FIX?] Assumes csbi.wAttributes only contains a color value
		*this = get_cons_console_color(csbi.wAttributes);
	}

	ConsoleColor::ConsoleColor(const color foreground, 
							   const color background) noexcept
		: foreground_(foreground)
		, background_(background)
	{}

	void ConsoleColor::set_foreground_color(const color foreground) noexcept
	{
		foreground_ = foreground;
	}

	void ConsoleColor::set_background_color(const color background) noexcept
	{
		background_ = background;
	}

	ConsoleColor::color ConsoleColor::get_foreground_color() const noexcept
	{
		return foreground_;
	}

	ConsoleColor::color ConsoleColor::get_background_color() const noexcept
	{
		return background_;
	}

	WORD ConsoleColor::get_windows_console_color(const ConsoleColor cons_color)
	{
		const auto fg = static_cast<WORD>(cons_color.foreground_);
		const auto bg = static_cast<WORD>(cons_color.background_);
		return fg + static_cast<WORD>(16) * bg;
	}

	ConsoleColor ConsoleColor::get_cons_console_color(const WORD windows_color)
	{
		const WORD bg = windows_color / static_cast<WORD>(16);
		const WORD fg = windows_color % static_cast<WORD>(16);
		return ConsoleColor(static_cast<color>(fg), static_cast<color>(bg));
	}

	char const* SetConsoleTextAttributeFailureException::what() const
	{
		return "\nWINDOWS CONSOLE API FAILURE!\nFAILED CALL TO "
			"SetConsoleTextAttribute(HANDLE, WORD)";
	}

	InvalidConsoleColorValueException::InvalidConsoleColorValueException()
		: InvalidConsoleEnumValueException("ConsoleColor::color")
	{}
} // namespace cons
