/*
 Code by Drake Johnson
*/
#include "output/println/textf.hpp"
#include <exception>

namespace cons
{
	// Exception struct for invalid enum class values
	struct InvalidEnumValueException : std::exception
	{
	private:
		const char* m_enum_name;

	public:
		InvalidEnumValueException(const char* enum_name) :
			m_enum_name(enum_name)
		{}

		[[nodiscard]] const char* what() const override
		{
			const auto pref = "\nINVALID ";
			const auto mid = " VALUE!\nWAS AN INVALID VALUE CASTED TO ";
			const auto suff = "?\n";

			const auto name_size = strlen(m_enum_name);
			const auto pref_size = strlen(pref);
			const auto mid_size = strlen(mid);
			const auto suff_size = strlen(suff);
			const auto err_size = name_size * 2 + pref_size + mid_size + suff_size + 1;

			auto err = std::make_unique<char[]>(err_size);
			err[err_size - 1] = '\0';

			memcpy(err.get(), pref, pref_size);
			auto pos = pref_size;

			memcpy(err.get() + pos, m_enum_name, name_size);
			pos += name_size;

			memcpy(err.get() + pos, mid, mid_size);
			pos += mid_size;

			memcpy(err.get() + pos, m_enum_name, name_size);
			pos += name_size;

			memcpy(err.get() + pos, suff, suff_size);

			return err.get();
		}
	};

	/**
	 Exception struct for invalid ConsoleColor values
	*/
	struct InvalidConsoleColorValueException : InvalidEnumValueException
	{
		InvalidConsoleColorValueException() :
			InvalidEnumValueException("ConsoleColor")
		{}
	};
	
	/**
	 Exception struct for invalid Layer values
	*/
	struct InvalidLayerValueException : InvalidEnumValueException
	{
		InvalidLayerValueException() :
			InvalidEnumValueException("Layer")
		{}
	};

	const char* WindowsConsoleFailureException::what() const
	{
		return "\nWINDOWS CONSOLE API FAILURE!\nPLEASE REVIEW THE CALL STACK!\n";
	}


	WORD textf::getWinColorCode(ConsoleColor color)
	{
		return static_cast<WORD>(color);
	}

	WORD textf::getWinColor(const ConsoleColor fg, const ConsoleColor bg)
	{
		return getWinColorCode(fg) + 16 * getWinColorCode(bg);
	}

	WORD textf::setup_console() const
	{
		HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		WORD old_attrib = -1;

		try
		{
			// Get console info
			if (!GetConsoleScreenBufferInfo(hout, &csbi))
			{
				throw WindowsConsoleFailureException();
			}

			// Save old colors
			old_attrib = csbi.wAttributes;

			// Set new color
			if (!SetConsoleTextAttribute(
				hout, getWinColor(m_foreground_color, m_background_color)))
			{
				throw WindowsConsoleFailureException();
			}
		}
		catch (const WindowsConsoleFailureException & e)
		{
			std::cerr << e.what() << std::endl;
		}

		return old_attrib;
	}

	void textf::restore_console(const WORD old_attribs) const
	{
		try
		{
			// Set color back
			if (!SetConsoleTextAttribute(
				GetStdHandle(STD_OUTPUT_HANDLE), old_attribs))
			{
				throw WindowsConsoleFailureException();
			}
		}
		catch (const WindowsConsoleFailureException & e)
		{
			println<decltype(e.what())> p(e.what());
		}
	}

	textf::textf()
		: textf("")
	{}

	textf::textf(const std::string_view text)
		: m_text(text)
		, m_foreground_color(ConsoleColor::bright_white)
		, m_background_color(ConsoleColor::black)
	{}

	void textf::display() const
	{
		const auto old_attribs = setup_console();
		std::cout << m_text;
		restore_console(old_attribs);
	}

	ConsoleColor textf::getColor(const Layer layer) const
	{
		try
		{
			switch (layer)
			{
			case Layer::foreground:
				return m_foreground_color;

			case Layer::background:
				return m_background_color;

			default:
				throw InvalidLayerValueException();
			}
		}
		catch (const InvalidLayerValueException & e)
		{
			println<decltype(e.what())> p(e.what());
			exit(1);
		}
	}

	void textf::set_color(const Layer layer, const ConsoleColor color)
	{
		try
		{
			switch (layer)
			{
			case Layer::foreground:
				m_foreground_color = color;
				break;

			case Layer::background:
				m_background_color = color;
				break;

			default:
				throw InvalidLayerValueException();
			}
		}
		catch (const InvalidLayerValueException & e)
		{
			println<decltype(e.what())> p(e.what());
			exit(1);
		}
	}

	void textf::modify_color(const Layer layer, const ConsoleColor color)
	{
		WORD new_win_color;
		auto m_fg_win = getWinColorCode(m_foreground_color);
		auto m_bg_win = getWinColorCode(m_background_color) * 16;

		try
		{
			switch (layer)
			{
			case Layer::foreground:
				new_win_color = getWinColorCode(color);
				m_fg_win |= new_win_color;
				m_foreground_color = static_cast<ConsoleColor>(m_fg_win);
				break;

			case Layer::background:
				new_win_color = getWinColorCode(color) * 16;
				m_bg_win |= new_win_color;
				m_background_color = static_cast<ConsoleColor>(m_bg_win);
				break;

			default:
				throw InvalidLayerValueException();
			}
		}
		catch (const InvalidLayerValueException & e)
		{
			println<decltype(e.what())> p(e.what());
			exit(1);
		}
	}
} // namespace cons
