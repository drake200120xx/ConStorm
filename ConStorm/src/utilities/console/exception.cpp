/*
 Code by Drake Johnson

 Defines various exception classes
*/
#include <cons/utilities/console/exception.hpp>
#include <cstring>
#include <memory>

namespace cons
{
	const char* WindowsConsoleFailureException::what() const
	{
		return "\nWINDOWS CONSOLE API FAILURE!\nPLEASE REVIEW THE CALL STACK!\n";
	}

	char const* CurrentWindowsScreenBufferFailureException::what() const
	{
		return "\nWINDOWS CONSOLE API FAILURE!\nFAILED CALL TO "
			"GetConsoleScreenBufferInfo(HANDLE, CONSOLE_SCREEN_BUFFER_INFO)\n";
	}

	InvalidConsoleEnumValueException::InvalidConsoleEnumValueException(const char* enum_name)
		: enum_name_(enum_name)
	{}

	const char* InvalidConsoleEnumValueException::what() const
	{
		const auto pref = "\nINVALID ";
		const auto mid = " VALUE!\nWAS AN INVALID VALUE CASTED TO ";
		const auto suff = "?\n";

		const auto name_size = strlen(enum_name_);
		const auto pref_size = strlen(pref);
		const auto mid_size = strlen(mid);
		const auto suff_size = strlen(suff);
		const auto err_size = name_size * 2 + pref_size + mid_size + suff_size + 1;

		auto err = std::make_unique<char[]>(err_size);
		err[err_size - 1] = '\0';

		memcpy(err.get(), pref, pref_size);
		auto pos = pref_size;

		memcpy(err.get() + pos, enum_name_, name_size);
		pos += name_size;

		memcpy(err.get() + pos, mid, mid_size);
		pos += mid_size;

		memcpy(err.get() + pos, enum_name_, name_size);
		pos += name_size;

		memcpy(err.get() + pos, suff, suff_size);

		return err.get();
	}
} // namespace cons
