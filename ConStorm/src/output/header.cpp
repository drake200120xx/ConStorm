/*
 Code by Drake Johnson
*/
#include "output/header.hpp"
#include "output/prompt.hpp"

namespace cons
{
	COORD Header::U_COORD::getShort() const
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

		if (this == &other)
			is_equ = true;
		else if (X == other.X && Y == other.Y)
			is_equ = true;

		return is_equ;
	}

	void Header::display() const
	{
		const auto old_attribs = setup_console();
		print(m_text);
		m_cursor_location.Y++; // Dashed line on next line
		const auto dummy_attribs = setup_console(); // Reposition cursor
		prompt(std::string(m_text.size() + 2, '-'));
		restore_console(old_attribs);
	}

	void Header::setConsoleCursor(U_COORD position)
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
			m_cursor_location = position;
			update_cursor_ = false;
		}
	}

	Header::U_COORD Header::getConsoleCursorPos()
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

	Header::U_COORD Header::getLiveConsoleCursor()
	{
		auto cx = static_cast<unsigned>(-1);
		auto cy = static_cast<unsigned>(-1);

		return U_COORD{ cx, cy };
	}

	WORD Header::setup_console() const
	{
		const auto old_attribs = textf::setup_console();

		auto hout = GetStdHandle(STD_OUTPUT_HANDLE);

		try
		{
			if (m_cursor_location == getLiveConsoleCursor())
				m_cursor_location = getConsoleCursorPos();

			if (!SetConsoleCursorPosition(hout, m_cursor_location.getShort()))
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
			m_cursor_location = getLiveConsoleCursor();
		else // Restore back to original
			m_cursor_location.Y--;
	}
} // namespace cons
