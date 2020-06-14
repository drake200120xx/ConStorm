/*
 Code by Drake Johnson

 Defines the ConsoleWindow class
*/
#include <cons/utilities/console/window.hpp>

namespace cons
{
	ConsoleWindow::ConsoleWindow(ConsoleFont font, const ConsoleColor color) noexcept
		: font_(std::move(font))
		, color_(color)
	{}

	void ConsoleWindow::apply_to_console() const
	{
		const auto hout = GetStdHandle(STD_OUTPUT_HANDLE);

		// Set colors
		const auto win_color = ConsoleColor::get_windows_console_color(color_);
		if (!SetConsoleTextAttribute(hout, win_color))
			throw SetConsoleTextAttributeFailureException();

		// Set font
		auto win_font = ConsoleFont::get_windows_console_font(font_);
		if (!SetCurrentConsoleFontEx(hout, false, &win_font))
			throw CurrentWindowsConsoleFontFailureException();
	}

	void ConsoleWindow::reset_color() const
	{
		const auto hout = GetStdHandle(STD_OUTPUT_HANDLE);

		// Set to original colors
		const auto win_color = ConsoleColor::get_windows_console_color(
			original_color_);
		if (!SetConsoleTextAttribute(hout, win_color))
			throw SetConsoleTextAttributeFailureException();
	}

	void ConsoleWindow::reset_font() const
	{
		const auto hout = GetStdHandle(STD_OUTPUT_HANDLE);

		// Set to original font
		auto win_font = ConsoleFont::get_windows_console_font(
			original_font_);
		if (!SetCurrentConsoleFontEx(hout, false, &win_font))
			throw CurrentWindowsConsoleFontFailureException();
	}

	void ConsoleWindow::set_color(const ConsoleColor color)
	{
		color_ = color;
	}

	void ConsoleWindow::set_foreground_color(ConsoleColor::color fg_color)
	{
		color_.set_foreground_color(fg_color);
	}

	void ConsoleWindow::set_background_color(ConsoleColor::color bg_color)
	{
		color_.set_background_color(bg_color);
	}

	void ConsoleWindow::set_font(ConsoleFont font)
	{
		font_ = std::move(font);
	}

	void ConsoleWindow::set_font_family(const ConsoleFont::family family)
	{
		font_.set_family(family);
	}

	void ConsoleWindow::set_font_size(const ConsoleFont::size size)
	{
		font_.set_size(size);
	}

	ConsoleFont ConsoleWindow::get_original_font() const
	{
		return original_font_;
	}

	ConsoleFont ConsoleWindow::get_font() const
	{
		return font_;
	}

	ConsoleColor ConsoleWindow::get_original_color() const
	{
		return original_color_;
	}

	ConsoleColor ConsoleWindow::get_color() const
	{
		return color_;
	}
} // namespace cons
