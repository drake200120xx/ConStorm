# ConStorm
A small C++ library for abstracting basic console IO functions

This is a side-project I've been working on for a couple of months to teach myself C++ and make console IO (something I have to do more than I'd like to admit) easier. Currently, the library only has support for Windows. However, there are various function that work independent of the OS. There are a few main things this library can do:
 - Print different object types to the console with simple syntax with the `cons::print()` function
 - Get validated user input of any "inputtable" type with the `cons::input<T>()` function
 - Create "Menu" objects, which build on a lot of IO functions to decrease speed
 - Automate basic file IO with input and output file streams with `cons::File`.
 
## Building
The library, on my end, is built with MSVC 2019 in C++17 using Visual Studio 2019 (version 16.4.5 as of writing this). To create the VS solution and project files, simply run `GenerateProjs.bat`. The build system uses Premake 5. No functionality should be compilier specific since most everything is either based on Windows console APIs or the STL.


## Output Functionality
The `cons::println<T>` system was the first thing I coded in this library. `cons::println<T>` is a class that has many different template specializations. It is not recommended to instantiate an object of this class directly. Instead, use functions like `cons::print()` or `cons::prompt()`.
 
### Using the `cons::print()` and `cons::prompt()` Functions
The syntax of this function is described in detail in `./cons/output/print.hpp`. The function signature looks like
```cpp
template<class LnTy, class... OtherLnTy>
void print(LnTy line, OtherLnTy... others);
```
Additionally, there is an default overload that flushes the `std::cout` stream. The function supports a variable number of arguments, allowing for function calls like
```cpp
cons::print(
  "This is line 1",
  "This is line 2",
  "This is line 3",
);
```

Types supported are:
 - Any type with an overloaded `<<` operator for `std::ostream` objects
 - `std::vector`, `std::set`, and `std::unordered_set`
 - `cons::textf`, `cons::Header`, and `cons::WordWrap`
 
Every argument sent to the `cons::print()` function will be on its own line. For containers (such as `std::vector`), each element is printed on its own line. The differences between the `cons::print()` and `cons::prompt()` function are small. `cons::prompt()` only takes in a maximum of one argument, has a default parameter value of `"Enter: "`, and does not move to a new line after the function call.

A way to add support for any given type is to specialize the `cons::println<T>` class, which is fairly straightforward. The classes rely on partial template specialization for containers, but non-containers can be specialized like so,
```cpp
namespace cons
{
  template<>
  class println</* Type */>
  {
    using ty = /* Type */;
    
  public:
    println(const ty& line)
    { // For example...
      line.display();
    }
  }
}
```

For SFINAE, simply specialize the second template parameter with `std::enable_if_t` (this is great for polymorphic types). After support has been added to the `cons::println` system, the `cons::print()` or `cons::prompt()` functions will automatically call the appropiate specializations.

### Using `cons::WordWrap`
This class takes in an `std::string` or `const char*` and wraps it based on how many characters are allowed per line (which is a parameter). Additionally, a final parameter allows specificiation on how many spaces to convert a `\t` character to. Refer to `./cons/output/word_wrap.hpp` for futher information.


## Input Functionality
The input validation function is extremely useful. There are two overloads (and a `std::string` template specialization for each of the overloads). The function signatures for the `cons::input()` functions are:
```cpp
// For validation with a function pointer, std::function, or lambda
template<class InTy>
InTy input(
  std::function<bool(InTy)> valid_func = [](InTy dummy) -> bool { return true; },
  const std::string& invalid_msg       = "Invalid input. Re-enter: "
);

// For validation with a set of valid inputs
template<class InTy>
InTy input(
  std::unordered_set<InTy> valid_set,
  const std::string& invalid_msg = "Invalid input. Re-enter: "
);
```
For further documentation on this function, refer to `./cons/input/input_function.hpp` or `./cons/input/input_set.hpp`

Additionally, there is also a `cons::pause()` command that pauses the current thread and waits for the user to enter a character.


## Menu Functionality
The Menu classes all serve different functions. It is best to review the commented documentation by referring to the `.hpp` files in `./cons/menus/`. To start an application loop, make the menus, chain them together, and pass the address to your beginning menu to `cons::menu_loop()`. Chaining menus together simply refers to configuring the `cons::MenuInterface*` that the `run()` method will return. Here is an example with a few different types of menus:
```cpp
// Make a Menu object
cons::Menu main_menu("Main Menu");
main_menu.set_description(
	"This is the main menu. Below, select the number that "
	"corresponds with your preferred option.", 
	40 // character-per-line limit for word wrapping
);
main_menu.set_prompt_msg("Enter the numerical option: ");

// Make an InfoMenu object
cons::InfoMenu app_help("Application Help");
// This (below) chains 'main_menu' to 'app_menu', meaning app_help's run()
// method will return a pointer to main_menu.
app_help.set_goto_next(&main_menu);

// Append sections sto app_help
app_help.append_section(
	"Getting Started", // Section header
	"To get started, you must ... " // Section text 
);

// Make InputMenu object
cons::InputMenu<std::string> user_name_menu("User Name Entry");
user_name_menu.set_description(
	"Below, enter your username to login. If you don't have a username, "
	"simply enter what you'd like yours to be."
);
// Set input validation function (in this case, make sure the user entered a value
// for the username
user_name_menu.set_validation(
	[](std::string user_input) -> bool
	{
		if (user_input.empty())
			return false;
		return true;
	}
);
user_name_menu.set_goto_next(&main_menu);

// Now, make an exit menu
cons::ExitMenu exit_menu("Press something to close this application...");

// Finally, chain all the menus to main_menu as "options"
main_menu.append_option(
	"Get help", // Description
	&app_help // Pointer to menu to go to if the user selects this option
);
main_menu.append_option("Login", &user_name_menu);
main_menu.append_option("Exit", &exit_menu);

// Pass starting menu (in this case main_menu) to application loop
cons::menu_loop(&main_menu);
```

For further questions, consult the commented documentation.
