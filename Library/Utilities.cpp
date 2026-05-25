#include "Utilities.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

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

void Utilities::logAndThrow(std::string message) {
	std::cerr << message;
	throw std::runtime_error(message);
}