/*
 Code by Drake Johnson
*/

#include <cons/output/header.hpp>
#include <cons/output/prompt.hpp>

namespace cons
{
	COORD Header::U_COORD::get_short() const
	{
		return { static_cast<SHORT>(X), static_cast<SHORT>(Y) };
	}
	Header::U_COORD& Header::U_COORD::operator=(U_COORD other)
	{
		if (this != &other)
		{
			X = other.X;
			Y = other.Y;
		}

		return *this;
	}
	bool Header::U_COORD::operator==(U_COORD other)
	{
		bool is_equ = false;

		if (this == &other || (X == other.X && Y == other.Y))
			is_equ = true;

		return is_equ;
	}

	Header::Header(std::string text)
		: textf(std::move(text))
		, cursor_location_(get_live_console_cursor())
		, update_cursor_(true)
	{}

	void Header::display() const
	{
		const auto old_attribs = setup_console();
		print(text_);
		cursor_location_.Y++; // Dashed line on next line
		const auto dummy_attribs = setup_console(); // Reposition cursor
		prompt(std::string(text_.size() + 2, '-'));
		restore_console(old_attribs);
	}

	void Header::set_console_cursor(U_COORD position)
	{
		HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;

		// Get number of char cells in current buffer
		if (!GetConsoleScreenBufferInfo(hstdout, &csbi))
			return;

		const auto& maxX = static_cast<unsigned>(csbi.dwSize.X);
		const auto& maxY = static_cast<unsigned>(csbi.dwSize.Y);

		if (position.X <= maxX && position.Y <= maxY)
		{
			cursor_location_ = position;
			update_cursor_ = false;
		}
	}

	void Header::set_console_cursor(const unsigned x, const unsigned y)
	{
		set_console_cursor({ x, y });
	}

	Header::U_COORD Header::get_console_cursor() const
	{
		return cursor_location_;
	}

	Header::U_COORD Header::get_console_cursor_pos()
	{
		HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(hstdout, &csbi);

		U_COORD pos
		{
			static_cast<unsigned>(csbi.dwCursorPosition.X),
			static_cast<unsigned>(csbi.dwCursorPosition.Y)
		};

		return pos;
	}

	Header::U_COORD Header::get_live_console_cursor()
	{
		static constexpr auto cx = static_cast<unsigned>(-1);
		static constexpr auto cy = static_cast<unsigned>(-1);

		return U_COORD{ cx, cy };
	}

	WORD Header::setup_console() const
	{
		const auto old_attribs = textf::setup_console();

		auto hout = GetStdHandle(STD_OUTPUT_HANDLE);

		try
		{
			if (cursor_location_ == get_live_console_cursor())
				cursor_location_ = get_console_cursor_pos();

			if (!SetConsoleCursorPosition(hout, cursor_location_.get_short()))
				throw WindowsConsoleFailureException();
		}
		catch (const WindowsConsoleFailureException& e)
		{
			std::cerr << e.what() << std::endl;
		}

		return old_attribs;
	}

	void Header::restore_console(const WORD old_attribs) const
	{
		textf::restore_console(old_attribs);

		// Set cursor location if `update_cursor_`
		if (update_cursor_) // Reset back to "live cursor" value
			cursor_location_ = get_live_console_cursor();
		else // Restore back to original
			cursor_location_.Y--;
	}
} // namespace cons
