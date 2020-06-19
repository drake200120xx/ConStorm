/*
 Code by Drake Johnson

 Displays multi-colored text in a windows console
*/
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
	 header.set_text("Heading 1");
	 
	 // Reset color attributes to 0
	 header.reset_color();
	 
	 // Set foreground and background colors
	 header.set_foreground_color(cons::ConsoleColor::color::purple);
	 header.set_background_color(cons::ConsoleColor::color::white);
	 
	 // Set position for first letter of header
	 header.set_cursor_location(0, 0);
	 @endcode
	*/
	class Header : public textf
	{
	private:
		struct U_COORD
		{
			mutable unsigned X;
			mutable unsigned Y;

			[[nodiscard]] COORD get_short() const;

			U_COORD& operator=(U_COORD other);
			bool operator==(U_COORD other);
		};

	public:
		Header(std::string text = "");

		void display() const override;

		void set_console_cursor(U_COORD position);
		void set_console_cursor(unsigned x, unsigned y);

		/**
		 @returns The position of the console's cursor as a U_COORD struct
		*/
		[[nodiscard]] U_COORD get_console_cursor() const;

	private:
		// INHERITED VARIABLES      //
		// std::string_view text_;  //
		// ConsoleColor color_;     //

		mutable U_COORD cursor_location_;
		bool update_cursor_;

		static U_COORD get_console_cursor_pos();
		static U_COORD get_live_console_cursor();

		[[nodiscard]] WORD setup_console() const override;
		void restore_console(WORD old_attribs) const override;
	};
} // namespace cons
#   else // Not Windows system
	// NOTE: Only Windows is supported for this header!
	// If not using Windows, this header should cause a linker
	// error.
#   endif // _WIN32
#endif // !CONS_HEADER_HEADER__
