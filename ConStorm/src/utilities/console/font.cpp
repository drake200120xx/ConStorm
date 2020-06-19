/*
 Code by Drake Johnson

 Defines the ConsoleFont class
*/
#include <cons/utilities/console/font.hpp>
#include <vector>

namespace cons
{
	ConsoleFont::ConsoleFont(void*) noexcept
		: family_(family::other)
		, size_(size::other)
	{}

	std::wstring ConsoleFont::family_to_string(const family value)
	{
		std::wstring name;

		switch (value)
		{
		case family::consolas:
			name = L"Consolas";
			break;

		case family::courier_new:
			name = L"Courier New";
			break;

		case family::lucida_console:
			name = L"Lucida Console";
			break;

		case family::ms_gothic:
			name = L"MS Gothic";
			break;

		case family::nsimsun:
			name = L"NSimSun";
			break;

		default:
			name = L"OTHER";
			break;
		}

		return name;
	}

	ConsoleFont::ConsoleFont()
		: family_(family::other)
		, size_(size::other)
	{
		HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_FONT_INFOEX current_font;
		current_font.cbSize = sizeof(CONSOLE_FONT_INFOEX);

		if (!GetCurrentConsoleFontEx(hout, false, &current_font))
			throw CurrentWindowsConsoleFontFailureException();

		*this = get_cons_font(current_font);
	}

	ConsoleFont::ConsoleFont(const family font_family, 
		const size font_size) noexcept
		: family_(font_family)
		, size_(font_size)
	{}

	ConsoleFont::ConsoleFont(const ConsoleFont& other)
		: ConsoleFont(nullptr)
	{
		copy(*this, other);
	}

	ConsoleFont::ConsoleFont(ConsoleFont&& other) noexcept
		: ConsoleFont(nullptr)
	{
		move(*this, std::move(other));
	}

	ConsoleFont& ConsoleFont::operator=(const ConsoleFont& other)
	{
		if (this != &other)
			copy(*this, other);
		return *this;
	}

	ConsoleFont& ConsoleFont::operator=(ConsoleFont&& other) noexcept
	{
		if (this != &other)
			move(*this, std::move(other));
		return *this;
	}

	void ConsoleFont::set_family(const family font_family)
	{
		if (font_family != family::other)
			family_ = font_family;
	}

	void ConsoleFont::set_size(const size font_size)
	{
		if (font_size != size::other)
			size_ = font_size;
	}

	ConsoleFont::family ConsoleFont::get_family() const
	{
		return family_;
	}

	ConsoleFont::size ConsoleFont::get_size() const
	{
		return size_;
	}

	CONSOLE_FONT_INFOEX ConsoleFont::get_windows_console_font(const ConsoleFont& font)
	{
		CONSOLE_FONT_INFOEX converted_font;
		converted_font.cbSize = sizeof(CONSOLE_FONT_INFOEX);
		converted_font.nFont = 0;
		converted_font.dwFontSize.X = 0;
		converted_font.FontFamily = FF_DONTCARE;
		converted_font.FontWeight = FW_NORMAL;

		SHORT height_y;
		switch (font.size_)
		{
		case size::other:
			height_y = static_cast<SHORT>(size::pt_12);
			break;

		default:
			height_y = static_cast<SHORT>(font.size_);
			break;
		}
		converted_font.dwFontSize.Y = height_y;

		std::wstring font_name;

		switch (font.family_)
		{
		case family::other:
			font_name = family_to_string(family::consolas);
			break;

		default:
			font_name = family_to_string(font.family_);
			break;
		}

		wcscpy_s(converted_font.FaceName, font_name.c_str());
		return converted_font;
	}

	ConsoleFont ConsoleFont::get_cons_font(const CONSOLE_FONT_INFOEX& font)
	{
		ConsoleFont converted_font(family::other, size::other);

		static constexpr auto sizeof_family_enum =
			static_cast<size_t>(family::other) + 1;
		// Deconstruct the current font to get the font family
		for (size_t i = 0; i < sizeof_family_enum; ++i)
		{
			const auto family_value = static_cast<family>(i);
			if (family_to_string(family_value) == font.FaceName)
			{
				converted_font.family_ = family_value;
				break;
			}
		}

		// Deconstruct the current font to get the font size
		const std::vector<unsigned> size_values{ 10, 12, 14, 16, 18, 24, 36 };
		std::vector<unsigned long> size_value_deviation;
		size_value_deviation.resize(size_values.size());

		for (const auto& value : size_values)
			// Must use lots of casts here to ensure no ambiguous function 
			// calls and to cast it into its needed type at the end
			size_value_deviation.push_back(static_cast<unsigned long>(abs(
				static_cast<long long>(value) - font.dwFontSize.Y)));

		auto min_size_deviation = size_value_deviation.at(0);
		size_t min_size_deviation_index = 0;
		for (size_t i = 1; i < size_value_deviation.size(); ++i)
		{
			if (min_size_deviation > size_value_deviation.at(i))
			{
				min_size_deviation = size_value_deviation.at(i);
				min_size_deviation_index = i;
			}
		}

		converted_font.size_ = static_cast<size>(size_values.at(
			min_size_deviation_index));

		return converted_font;
	}

	void ConsoleFont::copy(ConsoleFont& dest, const ConsoleFont& src)
	{
		dest.family_ = src.family_;
		dest.size_ = src.size_;
	}

	void ConsoleFont::move(ConsoleFont& dest, ConsoleFont&& src) noexcept
	{
		dest.family_ = src.family_;
		dest.size_ = src.size_;
	}

	char const* CurrentWindowsConsoleFontFailureException::what() const
	{
		return "\nWINDOWS CONSOLE API FAILURE!\nFAILED CALL TO "
			"[Get/Set]CurrentConsoleFontInfoEx(HANDLE, BOOL, "
			"PCONSOLE_FONT_INFOEX)\n";
	}

	InvalidConsoleFontFamilyValueException::InvalidConsoleFontFamilyValueException()
		: InvalidConsoleEnumValueException("ConsoleFont::family")
	{}

	InvalidConsoleFontSizeValueException::InvalidConsoleFontSizeValueException()
		: InvalidConsoleEnumValueException("ConsoleFont::size")
	{}
} // namespace cons
