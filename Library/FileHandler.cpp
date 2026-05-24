#include "FileHandler.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>

void FileHandler::checkIfOpen(const std::ifstream& file) {
	if (!file.is_open()) {
		std::cerr << "Couldn't open file for reading\n";
		throw std::runtime_error("Couldn't open file for reading");
	}
}

void FileHandler::checkIfOpen(const std::ofstream& file) {
	if (!file.is_open()) {
		std::cerr << "Couldn't open file for writing\n";
		throw std::runtime_error("Couldn't open file for writing");
	}
}