#pragma once
#include <fstream>
#include <string>

struct Utilities {
	static void checkIfOpen(const std::ifstream&);
	static void checkIfOpen(const std::ofstream&);
	static void logAndThrow(std::string);
	static void skipLines(std::ifstream&, unsigned);
};
