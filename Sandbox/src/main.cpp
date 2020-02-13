#include "output.hpp"
#include "input.hpp"


int main()
{
	auto dummy = cons::input<std::string>();
	cons::print("", "Input selected: ", dummy);
}
