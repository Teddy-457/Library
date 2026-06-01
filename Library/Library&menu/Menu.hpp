#pragma once
#include "Library.hpp"

//#define AUTO_OPEN_LIBRARY_DAT
//#define AUTO_LOGIN_JOHN_PORK

/// \class Menu
/// \brief A singleton class that manages the interactive command-line interface.
///
/// The Menu class handles reading user input from the standard input, parsing
/// commands, gathering necessary arguments, and delegating execution to the
/// Library instance.
class Menu {
private:
	/// \brief Private default constructor to enforce the singleton pattern.
	Menu() = default;

public:
	// Deleted copy and move semantics to prevent multiple instances
	Menu(const Menu&) = delete;
	Menu& operator=(const Menu&) = delete;
	Menu(Menu&&) noexcept = delete;
	Menu& operator=(Menu&&) = delete;

	/// \brief Default destructor.
	~Menu() = default;

	/// \brief Retrieves the singleton instance of the Menu.
	/// \return A reference to the single static Menu instance.
	static Menu& getInstance();

	/// \brief Starts the main interactive loop.
	/// \param library A reference to the Library instance to execute commands against.
	///
	/// This function loops indefinitely, prompting the user for commands, enforcing
	/// login and privilege constraints, and executing library operations until
	/// the user inputs the "exit" command.
	void menu(Library& library);
};

// namespace Menu {
//	void menu(Library&);
//};