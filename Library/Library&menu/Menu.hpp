#pragma once
#include "Library.hpp"

//#define AUTO_OPEN_LIBRARY_DAT
//#define AUTO_LOGIN_JOHN_PORK

class Menu {
private:
	Menu() = default;

public:
	Menu(const Menu&) = delete;
	Menu& operator=(const Menu&) = delete;
	Menu(Menu&&) noexcept = delete;
	Menu& operator=(Menu&&) = delete;
	~Menu() = default;

	static Menu& getInstance();
	void menu(Library&);
};

// namespace Menu {
//	void menu(Library&);
//};