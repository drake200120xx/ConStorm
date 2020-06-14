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
#ifdef _WIN32
#include "master.hpp"
#include <cons/utilities/console.hpp>
#include <string_view>

namespace cons
{
	/**
	 Holds the information for formatted text. Currently, only a different 
	 color is supported.

	 A 'textf' object can be initialized with either no arguments or with text.
	 The color, by default, is a bright white foreground on a black background. 
	 To change this, use the 'set_color(layer, ConsoleColor)', the 
	 'set_foreground_color(ConsoleColor)', or the 
	 'set_background_color(ConsoleColor)' methods.

	 'layer' and 'ConsoleColor' are scoped enums. 'layer' can either be 
	 'layer::foreground', which refers to the text itself, or 
	 'layer::background', which refers to the background. The options for 
	 'ConsoleColor' are above.

	 Example usage:
	 @code
	 cons::textf blue_text;
	 blue_text.set_text("This text will be blue");
	 blue_text.set_foreground_color(ConsoleColor::color::blue);
	 blue_text.set_background_color(ConsoleColor::color::black);
	 
	 cons::textf red_text("This text will be red");
	 red_text.set_foreground_color(ConsoleColor::color::red);
	 // By default, background is black
	 
	 // If "print.hpp" is not included...
	 blue_text.display();
	 std::cout << '\n';
	 red_text.display();
	 std::cout << '\n';
	 
	 // Or, if "print.hpp" is included, cons::textf is supported and 
	 // display methods are automatically called
	 cons::print(blue_text, red_text);
	 @endcode

	 For further information, refer to the comments on the functions below.

	 @param text_  The text that will be formatted
	 @param color_ The color of the text and its background
	*/
	class textf
	{
	public:
		/**
		 Specifies the layer of the console to affect (foreground -- the 
		 text -- or background)
		*/
		enum class layer
		{
			foreground, 
			background
		};

		/**
		 Initializes with a text field of the specified text, a bright white foreground,
		 and a black background

		 @param text The text to display
		*/
		textf(std::string text = "");
		textf(const textf& other);
		textf(textf&& other) noexcept;
		virtual ~textf() = default;

		textf& operator=(const textf& other);
		textf& operator=(textf&& other) noexcept;

		virtual void display() const;


		/**
		 Modifies the color of the specified layer. For example, if the 
		 foreground color is red and 'modify_color(layer::foreground, 
		 ConsoleColor::color::blue)' is called, the foreground color will then 
		 turn purple because red + blue = purple.

		 The most important thing to note about this function is that it does 
		 NOT reset the color of the specified layer, it preforms a bitwise "OR" 
		 operation to the current color.

		 To make a color bright, use the 'ConsoleColor::color::gray' option, as 
		 the bitwise OR operation will automatically intensify the color.

		 @param layer Specifies whether to modify the foreground (text) color or 
		              background color
		 @param color The color to set the specified layer to
		*/
		void modify_color(layer layer, ConsoleColor color);

		/**
		 Resets the foreground color to bright white and the background color 
		 to black
		*/
		void reset_color();

		void set_text(std::string text);

		/**
		 Resets the foreground or background color to the color specified

		 @param color The color to set the specified layer to
		*/
		void set_color(ConsoleColor color);
		void set_foreground_color(ConsoleColor::color color);
		void set_background_color(ConsoleColor::color color);

		[[nodiscard]] std::string get_text() const;
		[[nodiscard]] ConsoleColor get_color() const;

		textf& operator=(std::string str);

	protected:
		std::string text_;
		ConsoleColor color_;

		static WORD get_win_color(ConsoleColor color);

		/**
		 Splits up the task of displaying the message. This is the setup phase 
		 and can be overridden.

		 @returns The old console attributes to save color information
		*/
		[[nodiscard]] virtual WORD setup_console() const;

		/**
		 Restores the old console attributes after displaying
		*/
		virtual void restore_console(WORD old_attribs) const;

		static void copy(textf& dest, const textf& src);
		static void move(textf& dest, textf&& src) noexcept;
	};

	template<class LnTy>
	/**
	 A template specialization of 'println' for a 'textf' object. Second 
	 template parameter for polymorphic support.
	*/
	class println <LnTy, std::enable_if_t<std::is_base_of_v<textf, LnTy>>>
	{
	public:
		println(const textf& line)
		{
			line.display();
		}
	};

	/**
	 Exception struct for invalid layer enum values
	*/
	struct InvalidConsoleLayerEnumValueException 
		: InvalidConsoleEnumValueException
	{
		InvalidConsoleLayerEnumValueException();
	};
} // namespace cons
#endif // _WIN32
#endif // !CONS_PRINTLN_COLORED_TEXT_HEADER__
