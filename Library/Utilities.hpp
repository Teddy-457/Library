#pragma once
#include <fstream>
#include <string>

/*struct*/ namespace Utilities {
	/*static*/ void checkIfOpen(const std::ifstream&);
	/*static*/ void checkIfOpen(const std::ofstream&);
	/*static*/ bool checkIfExists(const std::string&);
	/*static*/ void logAndThrow(std::string);
	/*static*/ void skipLines(std::ifstream&, unsigned);
	/*static*/ void clearCin();
};
