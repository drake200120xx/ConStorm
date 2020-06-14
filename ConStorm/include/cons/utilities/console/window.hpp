/**
 Code by Drake Johnson

 Contains the class which manages default console font and color
*/
#ifndef CONS_UTILITIES_CONSOLE_WINDOW_HEADER__
#define CONS_UTILITIES_CONSOLE_WINDOW_HEADER__
#ifdef _WIN32
#include "color.hpp"
#include "font.hpp"

namespace cons
{
	class ConsoleWindow
	{
	public:
		ConsoleWindow() = default;
		ConsoleWindow(ConsoleFont font, ConsoleColor color) noexcept;

		/**
		 Sets the font and color specified by 'font_' and 'color_',
		 respectively, to the console
		*/
		void apply_to_console() const;

		/**
		 Resets the console color to its color at the time of this object
		 creation
		*/
		void reset_color() const;

		/**
		 Resets the console color to its font at the time of this object
		 creation
		*/
		void reset_font() const;

		void set_color(ConsoleColor color);
		void set_foreground_color(ConsoleColor::color fg_color);
		void set_background_color(ConsoleColor::color bg_color);

		void set_font(ConsoleFont font);
		void set_font_family(ConsoleFont::family family);
		void set_font_size(ConsoleFont::size size);
		
		[[nodiscard]] ConsoleFont get_original_font() const;
		[[nodiscard]] ConsoleFont get_font() const;
		[[nodiscard]] ConsoleColor get_original_color() const;
		[[nodiscard]] ConsoleColor get_color() const;

	private:
		ConsoleFont original_font_, font_;
		ConsoleColor original_color_, color_;
	};
} // namespace cons
#endif // _WIN32
#endif // !CONS_UTILITIES_CONSOLE_WINDOW_HEADER__
