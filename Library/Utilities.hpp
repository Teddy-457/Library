#pragma once
#include <fstream>
#include <string>

/*struct*/ namespace Utilities {
	/*static*/ void checkIfOpen(const std::ifstream&);
	/*static*/ void checkIfOpen(const std::ofstream&);
	/*static*/ bool checkIfExists(const std::string&);
	/*static*/ void logAndThrow(const std::string&);
	/*static*/ void skipLines(std::ifstream&, unsigned);
	/*static*/ void clearCin();
	/*static*/ std::string to_lowercase(const std::string&);
	/*static*/ void stripWhitespaceFrontAndBack(std::string&);
	/*static*/ bool containsChar(const std::string&, char);
};
