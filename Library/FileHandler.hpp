#pragma once
#include <fstream>

class FileHandler {
public:
	void static checkIfOpen(const std::ifstream&);
	void static checkIfOpen(const std::ofstream&);
};
