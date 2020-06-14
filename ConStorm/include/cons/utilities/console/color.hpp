/*
 Code by Drake Johnson

 Contains the class which simplifies the Windows console API for colors
*/
#ifndef CONS_UTILITIES_CONSOLE_COLOR_HEADER__
#define CONS_UTILITIES_CONSOLE_COLOR_HEADER__
#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#	define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN
#include "exception.hpp"
#include <windows.h>

namespace cons
{
	/**
	 Contains the information for the default color profile of the console. This
	 class simplifies the Windows console color API
	*/
	class ConsoleColor
	{
	public:
		/**
		 Colors available for the `set_color()` functions (both foreground
		 and background)
		*/
		enum class color : WORD
		{
			black = 0,
			blue = FOREGROUND_BLUE,
			green = FOREGROUND_GREEN,
			aqua = FOREGROUND_GREEN | FOREGROUND_BLUE,
			red = FOREGROUND_RED,
			purple = FOREGROUND_RED | FOREGROUND_BLUE,
			yellow = FOREGROUND_RED | FOREGROUND_GREEN,
			white = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN,
			gray = FOREGROUND_INTENSITY,
			bright_blue = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
			bright_green = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
			bright_aqua = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
			bright_red = FOREGROUND_RED | FOREGROUND_INTENSITY,
			bright_purple = FOREGROUND_RED | FOREGROUND_BLUE,
			bright_yellow = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
			bright_white = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
		};

		/**
		 Sets the foreground and background colors to the console's current
		 foreground and background colors, respectively
		*/
		ConsoleColor();
		explicit ConsoleColor(color foreground, color background) noexcept;

		void set_foreground_color(color foreground) noexcept;
		void set_background_color(color background) noexcept;

		[[nodiscard]] color get_foreground_color() const noexcept;
		[[nodiscard]] color get_background_color() const noexcept;

		/**
		 Converts this object to a Windows console color and returns it

		 @returns Windows console API compatible color struct
		*/
		[[nodiscard]] static WORD get_windows_console_color(
			ConsoleColor cons_color);

		/**
		 Converts a Windows WORD object to a ConsoleColor object

		 @returns The converted ConsoleColor object
		*/
		[[nodiscard]] static ConsoleColor get_cons_console_color(
			WORD windows_color);

	private:
		color foreground_, background_;
	};

	/**
	 Exception struct for failed calls to SetConsoleTextAttribute()
	*/
	struct SetConsoleTextAttributeFailureException
		: WindowsConsoleFailureException
	{
		[[nodiscard]] char const* what() const override;
	};

	/**
	 Exception struct for invalid ConsoleColor values
	*/
	struct InvalidConsoleColorValueException : InvalidConsoleEnumValueException
	{
		InvalidConsoleColorValueException();
	};
} // namespace cons
#endif // _WIN32
#endif // !CONS_UTILITIES_CONSOLE_COLOR_HEADER__
