#pragma once
#include <fstream>
#include <string>

struct Utilities {
	void static checkIfOpen(const std::ifstream&);
	void static checkIfOpen(const std::ofstream&);
	static void logAndThrow(std::string);
};
