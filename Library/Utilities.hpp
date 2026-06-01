#pragma once
#include <fstream>
#include <string>

/// \namespace Utilities
/// \brief Helper functions for file IO, string manipulation, and error handling.
namespace Utilities {

	/// \brief Validates if an input file stream is open.
	/// \param file The input file stream to check.
	/// \throws std::runtime_error if the file stream is not open.
	void checkIfOpen(const std::ifstream& file);

	/// \brief Validates if an output file stream is open.
	/// \param file The output file stream to check.
	/// \throws std::runtime_error if the file stream is not open.
	void checkIfOpen(const std::ofstream& file);

	/// \brief Checks if a file exists on the filesystem.
	/// \param filename The path and name of the file to check.
	/// \return true if the file exists, false otherwise.
	bool checkIfExists(const std::string& filename);

	/// \brief Logs an error message to the console and throws a runtime exception.
	/// \param message The error message to log and throw.
	/// \throws std::runtime_error unconditionally.
	void logAndThrow(const std::string& message);

	/// \brief Skips a specified number of lines in an input file stream.
	/// \param file The input file stream to advance.
	/// \param lines The number of newline characters ('\n') to skip.
	void skipLines(std::ifstream& file, unsigned lines);

	/// \brief Clears the fail state of the standard input stream (std::cin) and flushes its buffer.
	/// 
	/// Used to recover from bad console input and prevent infinite loops.
	void clearCin();

	/// \brief Converts a given string to completely lowercase characters.
	/// \param str The string to convert.
	/// \return A new string containing the lowercase version of the input.
	std::string to_lowercase(const std::string& str);

	/// \brief Strips leading and trailing whitespace characters from a string in-place.
	/// \param str The string to modify.
	void stripWhitespaceFrontAndBack(std::string& str);

	/// \brief Checks if a specific character exists within a string.
	/// \param str The string to search inside.
	/// \param c The character to search for.
	/// \return true if the character is found, false otherwise.
	bool containsChar(const std::string& str, char c);
};
