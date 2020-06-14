/*
 Code by Drake Johnson

 Contains various exception classes for the Windows console in case
 Windows console API function return a failed state
*/
#ifndef CONS_UTILITIES_CONSOLE_EXCEPTION_HEADER__
#define CONS_UTILITIES_CONSOLE_EXCEPTION_HEADER__
#include <exception>

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
	 Exception struct for failed calls to GetConsoleScreenBufferInfo()
	*/
	struct CurrentWindowsScreenBufferFailureException
		: WindowsConsoleFailureException
	{
		[[nodiscard]] char const* what() const override;
	};

	/**
	 Exception struct for invalid enum class values (triggered when static
	 casting a numerical value to an enum class type)
	*/
	struct InvalidConsoleEnumValueException : WindowsConsoleFailureException
	{
	private:
		const char* enum_name_;

	public:
		InvalidConsoleEnumValueException(const char* enum_name);
		[[nodiscard]] const char* what() const override;
	};
} // namespace cons
#endif // !CONS_UTILITIES_CONSOLE_EXCEPTION_HEADER__
