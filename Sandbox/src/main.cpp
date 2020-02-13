#include "menus.hpp"


int main()
{
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
}
