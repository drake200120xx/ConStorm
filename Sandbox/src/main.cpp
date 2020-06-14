#include "menus.hpp"


int main()
{
	using namespace cons;
	WordWrap wrap(
		"This is a long string that will be wrapped.\n\tI'm not quite sure how many "
		"times it will be wrapped, but we will find out!", 30
	);
	print(
		"",
		wrap,
		""
	);
}
