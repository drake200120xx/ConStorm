/*
 Code by Drake Johnson

 Defines the textf object and provides an template
 specialization for using `println` with this object,
 thus adding its support through the library.

 Header includes:
   - master.hpp    : println
	 - <iostream> : cout
   - <exception>   : exception
   - <string_view> : string_view
   - <windows.h>   : CONSOLE_SCREEN_BUFFER_INFO, COORD, HANDLE, WORD
*/
#ifndef CONS_PRINTLN_COLORED_TEXT_HEADER__
#define CONS_PRINTLN_COLORED_TEXT_HEADER__
#ifdef _MSC_VER
#	pragma once
#endif //_MSC_VER
#ifdef _WIN32
#include "master.hpp"
#include <string_view>
#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif // !WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace cons
{
	/**
	 Exception for Windows console functions failures
	*/
	struct WindowsConsoleFailureException : std::exception
	{
		[[nodiscard]] const char* what() const override;
	};

	/**
	 Colors available for the `setColor()` functions (both foreground
	 and background)
	*/
	enum class ConsoleColor : WORD
	{
		black         = 0,
		blue          = FOREGROUND_BLUE     ,
		green         = FOREGROUND_GREEN    ,
		aqua          = FOREGROUND_GREEN    | FOREGROUND_BLUE     ,
		red           = FOREGROUND_RED      ,	    
		purple        = FOREGROUND_RED      | FOREGROUND_BLUE     ,
		yellow        = FOREGROUND_RED      | FOREGROUND_GREEN    ,
		white         = FOREGROUND_RED      | FOREGROUND_BLUE     | FOREGROUND_GREEN    ,
		gray          = FOREGROUND_INTENSITY,
		bright_blue   = FOREGROUND_BLUE     | FOREGROUND_INTENSITY,
		bright_green  = FOREGROUND_GREEN    | FOREGROUND_INTENSITY,
		bright_aqua   = FOREGROUND_GREEN    | FOREGROUND_BLUE     | FOREGROUND_INTENSITY,
		bright_red    = FOREGROUND_RED      | FOREGROUND_INTENSITY,
		bright_purple = FOREGROUND_RED      | FOREGROUND_BLUE     ,
		bright_yellow = FOREGROUND_RED      | FOREGROUND_GREEN    | FOREGROUND_INTENSITY,
		bright_white  = FOREGROUND_RED      | FOREGROUND_GREEN    | FOREGROUND_BLUE     | FOREGROUND_INTENSITY
	};

	/**
	 Specifies the "layer" to affect. 'Layer::foreground' affects the foreground/text
	 layer, while 'Layer::background' affects the background.
	*/
	enum class Layer
	{
		background,
		foreground
	};

	/**
	 Holds the information for formatted text. Currently, only a different color is supported.

	 A 'textf' object can be initialized with either no arguments or with text. The color, by
	 default, is a bright white foreground on a black background. To change this, use the
	 'set_color(Layer, ConsoleColor)', the 'set_foreground_color(ConsoleColor)', or the
	 'set_background_color(ConsoleColor)' methods.

	 'Layer' and 'ConsoleColor' are scoped enums. 'Layer' can either be 'Layer::foreground', which
	 refers to the text itself, or 'Layer::background', which refers to the background. The options
	 for 'ConsoleColor' are above.

	 Example usage:
	 @code
	     cons::textf blue_text;
		 blue_text.setText("This text will be blue");
		 blue_text.set_foreground_color(ConsoleColor::blue);
		 blue_text.set_background_color(ConsoleColor::black);

		 cons::textf red_text("This text will be red");
		 red_text.set_color(Layer::foreground, ConsoleColor::red);
		 // By default, background is black

		 // If "print.hpp" is not included...
		 blue_text.display();
		 std::cout << '\n';
		 red_text.display();
		 std::cout << '\n';

		 // Or, if "print.hpp" is included, cons::textf is supported and display methods are
		 // automatically called
		 cons::print(blue_text, red_text);
	 @endcode

	 For further information, refer to the comments on the functions below.

	 @param m_text             The text that will be formatted
	 @param m_foreground_color The foreground/text color
	 @param m_background_color The background color
	*/
	class textf
	{
	protected:
		std::string_view m_text;
		ConsoleColor m_foreground_color;
		ConsoleColor m_background_color;

		static WORD getWinColorCode(ConsoleColor color);
		static WORD getWinColor(ConsoleColor fg, ConsoleColor bg);

		/**
		 Splits up the task of displaying the message. This is the setup phase and
		 can be overridden.

		 @returns The old console attributes to save color information
		*/
		[[nodiscard]] virtual WORD setup_console() const;

		/**
		 Restores the old console attributes after displaying
		*/
		virtual void restore_console(WORD old_attribs) const;

	public:
		/**
		 Initializes with an empty text field, a bright white foreground, and a
		 black background
		*/
		textf();

		/**
		 Initializes with a text field of the specified text, a bright white foreground,
		 and a black background

		 @param text The text to display
		*/
		textf(std::string_view text);

		virtual ~textf() = default;

		virtual void display() const;

		[[nodiscard]] std::string getText() const
		{
			return std::string(m_text);
		}

		/**
		 Returns either the current foreground color (color of the text)
		 or the current background color, depending on the value of
		 `layer`

		 @param layer Specifies whether to return the foreground or background color
		 @returns Either the foreground or background color
		*/
		[[nodiscard]] ConsoleColor getColor(const Layer layer) const;
		[[nodiscard]] ConsoleColor getForegroundColor() const
		{
			return getColor(Layer::foreground);
		}
		[[nodiscard]] ConsoleColor getBackgroundColor() const
		{
			return getColor(Layer::background);
		}

		/**
		 Sets the value of `m_text` to the value of the `text` parameter. `text`, being an
		 std::string_view, can implicitly convert from a const char* or std::string object

		 @param text The value to set `m_text` to
		*/
		void setText(const std::string_view text)
		{
			m_text = text;
		}

		/**
		 Resets the foreground color to bright white and the background color to black
		*/
		void reset_color()
		{
			m_foreground_color = ConsoleColor::bright_white;
			m_background_color = ConsoleColor::black;
		}

		/**
		 Resets the foreground or background color to the color specified

		 @param layer Specifies whether to reset the foreground (text) color or background color
		 @param color The color to set the specified layer to
		*/
		void set_color(Layer layer, ConsoleColor color);
		void set_foreground_color(const ConsoleColor color)
		{
			set_color(Layer::foreground, color);
		}
		void set_background_color(const ConsoleColor color)
		{
			set_color(Layer::background, color);
		}

		/**
		 Modifies the color of the specified layer. For example, if the foreground color is
		 red and 'modify_color(Layer::foreground, ConsoleColor::blue)' is called, the foreground
		 color will then turn purple because red + blue = purple.

		 The most important thing to note about this function is that it does NOT reset the color
		 of the specified layer, it preforms a bitwise "OR" operation to the current color.

		 To make a color bright, use the 'ConsoleColor::gray' option, as the bitwise OR operation
		 will automatically intensify the color.

		 @param layer Specifies whether to modify the foreground (text) color or background color
		 @param color The color to set the specified layer to
		*/
		void modify_color(Layer layer, ConsoleColor color);
	};

	template<class LnTy>
	/**
	 A template specialization of 'println' for a 'textf' object. Second template
	 parameter for polymorphic support.
	*/
	class println <LnTy, std::enable_if_t<std::is_base_of_v<textf, LnTy>>>
	{
	public:
		println(const textf& line)
		{
			line.display();
		}
	};
} // namespace cons
#endif // _WIN32
#endif // !CONS_PRINTLN_COLORED_TEXT_HEADER__
