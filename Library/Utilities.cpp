#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <stdexcept>
#include "Utilities.hpp"

void Utilities::checkIfOpen(const std::ifstream& file) {
	if (!file.is_open()) {
		logAndThrow("Couldn't open file for reading");
	}
}

void Utilities::checkIfOpen(const std::ofstream& file) {
	if (!file.is_open()) {
		logAndThrow("Couldn't open file for writing");
	}
}

bool Utilities::checkIfExists(const std::string& filename) {
	std::ifstream file(filename);
	bool file_exists{file.good()};
	file.close();

	return file_exists;
}

void Utilities::logAndThrow(const std::string& message) {
	std::cerr << message;
	throw std::runtime_error(message);
}

void Utilities::skipLines(std::ifstream& file, unsigned lines) {
	for (unsigned i = 0; i < lines; ++i) {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void Utilities::clearCin() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string Utilities::to_lowercase(const std::string& string) {
	std::string str{ string };
	for (char& c : str) {
		c = std::tolower(c);
	}
	
	return str;
}

void Utilities::stripWhitespaceFrontAndBack(std::string& str) {
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] == ' ' && (i == 0 || i == str.size() - 1)) {
			str.erase(str.begin() + i);
		}
	}
}
