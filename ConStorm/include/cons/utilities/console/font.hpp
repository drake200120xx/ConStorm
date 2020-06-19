/*
 Code by Drake Johnson

 Contains the class which simplifies the Windows console API for fonts
*/
#ifndef CONS_UTILITIES_CONSOLE_FONT_HEADER__
#define CONS_UTILITIES_CONSOLE_FONT_HEADER__
#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#	define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN
#include "exception.hpp"
#include <string>
#include <windows.h>

namespace cons
{
	/**
	 Contains enums relevant to the console's font. This class is responsible
	 for simplifying the Windows console font API
	*/
	class ConsoleFont
	{
	private:
		/**
		 Used to initialize the member variables without setting them to be
		 the console's current font
		*/
		explicit ConsoleFont(void*) noexcept;

	public:
		/**
		 Font families available to set the console's text to
		*/
		enum class family
		{
			consolas       = 0,
			courier_new    = 1,
			lucida_console = 2,
			ms_gothic      = 3,
			nsimsun        = 4,
			other          = 5
		};

		/**
		 Converts a 'family' enum value to a string

		 @returns The name of 'family' enum value
		*/
		static std::wstring family_to_string(family value);

		/**
		 Font sizes available to set the console's text to
		*/
		enum class size : SHORT
		{
			pt_10 = 10,
			pt_12 = 12,
			pt_14 = 14,
			pt_16 = 16,
			pt_18 = 18,
			pt_24 = 24,
			pt_36 = 36,
			other = 7
		};

		/**
		 Default constructor stores the current console font as a ConsoleFont 
		 object in `this`
		*/
		ConsoleFont();
		ConsoleFont(family font_family, size font_size) noexcept;
		ConsoleFont(const ConsoleFont& other);
		ConsoleFont(ConsoleFont&& other) noexcept;
		~ConsoleFont() = default;

		ConsoleFont& operator=(const ConsoleFont& other);
		ConsoleFont& operator=(ConsoleFont&& other) noexcept;

		void set_family(family font_family);
		void set_size(size font_size);

		[[nodiscard]] family get_family() const;
		[[nodiscard]] size get_size() const;

		/**
		 Converts this object to a Windows console font and returns it

		 @param font The ConsoleFont object to convert
		 @returns Windows console API compatible font struct
		*/
		[[nodiscard]] static CONSOLE_FONT_INFOEX get_windows_console_font(
			const ConsoleFont& font);

		/**
		 Converts a Windows console font object to a ConsoleFont object and
		 returns it

		 @param font The Windows console font object to convert
		 @returns The converted ConsoleFont object
		*/
		[[nodiscard]] static ConsoleFont get_cons_font(
			const CONSOLE_FONT_INFOEX& font);

	private:
		family family_;
		size size_;

		static void copy(ConsoleFont& dest, const ConsoleFont& src);
		static void move(ConsoleFont& dest, ConsoleFont&& src) noexcept;
	};

	/**
	 Exception struct for a failed call to GetCurrentConsoleFontInfoEx() or
	 SetCurrentConsoleFontInfoEx()
	*/
	struct CurrentWindowsConsoleFontFailureException
		: WindowsConsoleFailureException
	{
		[[nodiscard]] char const* what() const override;
	};

	/**
	 Exception struct for an invalid ConsoleFont::family enum value
	*/
	struct InvalidConsoleFontFamilyValueException 
		: InvalidConsoleEnumValueException
	{
		InvalidConsoleFontFamilyValueException();
	};

	/**
	 Exception struct for an invalid ConsoleFont::size enum value
	*/
	struct InvalidConsoleFontSizeValueException
		: InvalidConsoleEnumValueException
	{
		InvalidConsoleFontSizeValueException();
	};
} // namespace cons
#endif // _WIN32
#endif // !CONS_UTILITIES_CONSOLE_FONT_HEADER__
