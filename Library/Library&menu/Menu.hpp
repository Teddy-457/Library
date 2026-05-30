#pragma once
#include "Library.hpp"

// namespace Menu {
//	void menu(Library&);
//};

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