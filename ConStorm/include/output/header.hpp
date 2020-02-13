/*
 Code by Drake Johnson

 Displays multi-colored text in a windows console

 Header includes:
   - print.hpp : print()
	 - println.hpp
	   - colored_text.hpp : textf, WindowsConsoleFailureException
		 - master.hpp
		   - <iostream>
		 - <exception>
		 - <string_view>
		 - <windows.h>
*/
#ifdef _MSC_VER
#	pragma once
#endif //_MSC_VER
#ifndef CONS_HEADER_HEADER__
#define CONS_HEADER_HEADER__
#include "print.hpp"
#ifdef _WIN32

namespace cons
{
	/**
	 The Header class creates a heading-style message. When the `display()` method
	 is called, the header will display fully formatted.

	 To set up a Header object, first make an object of the class with no parameters.
	 The properties of the header can then be modified through the setter methods. There
	 are also getter methods supplied. The header's properties are (1) the text of the
	 header, (2) the color of the text, and (3) the location of the cursor for the first
	 character of the header.

	 Default values for the properties are as follows:
	   - Text: "DEFAULT HEADER TEXT"
	   - Color: 15 (white foreground, black background)

	 After `display()` is called, the cursor will be moved to the next line.

	 Example usage:
	 @code
	 // Create Header object
	 cons::Header header;
	 
	 // Set header text
	 header.setText("Heading 1");
	 
	 // Reset color attributes to 0
	 header.resetColor();
	 
	 // Set foreground and background colors
	 header.setForegroundColor(cons::ConsoleColor::purple);
	 header.setBackgroundColor(cons::ConsoleColor::white);
	 
	 // Set position for first letter of header
	 header.setCursorLocation(0, 0);
	 @endcode
	*/
	class Header : public textf
	{
	private:
		struct U_COORD
		{
			mutable unsigned X;
			mutable unsigned Y;

			[[nodiscard]] COORD getShort() const;

			U_COORD& operator=(U_COORD other);
			bool operator==(U_COORD other);
		};

	public:
		Header() 
			: m_cursor_location(getLiveConsoleCursor())
			, update_cursor_(true)
		{}

		Header(const std::string_view text)
			: textf(text)
			, m_cursor_location(getLiveConsoleCursor())
			, update_cursor_(true)
		{}

		Header(const char* text)
			: Header(std::string_view(text))
		{}

		void display() const override;

		/**
		 @returns The position of the console's cursor as a U_COORD struct
		*/
		[[nodiscard]] U_COORD getConsoleCursor() const
		{
			return m_cursor_location;
		}

		void setConsoleCursor(U_COORD position);
		void setConsoleCursor(const unsigned x, const unsigned y)
		{
			setConsoleCursor({ x, y });
		}

	private:
		// INHERITED VARIABLES              //
		// std::string_view m_text;         //
		// ConsoleColor m_foreground_color; //
		// ConsoleColor m_background_color; //

		mutable U_COORD m_cursor_location;
		bool update_cursor_;

		static U_COORD getConsoleCursorPos();
		static U_COORD getLiveConsoleCursor();

		[[nodiscard]] WORD setup_console() const override;
		void restore_console(const WORD old_attribs) const override;
	};
} // namespace cons
#   else // Not Windows system
	// NOTE: Only Windows is supported for this header!
	// If not using Windows, this header should cause a linker
	// error.
#   endif // _WIN32
#endif // !CONS_HEADER_HEADER__
