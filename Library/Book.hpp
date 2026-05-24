#pragma once
#include <string>
#include <vector>

class Book {
private:
	std::string m_author;
	std::string m_title;
	std::string m_genre;
	std::string m_description;
	signed int m_year; //support for dates BC
	std::vector<std::string> m_tags;
	double m_rating;
	unsigned m_isbn;
};