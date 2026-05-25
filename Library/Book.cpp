#include <iostream>
#include <string>
#include "Book.hpp"

void Book::serialize(std::string filename) const {
	///~~check if book exists~~ check at Library level for duplicates instead
}

///Book* Book::deserialize(std::string filename, unsigned line) {
///	
///}

std::string Book::getTitle() const {
	return m_title;
}

std::string Book::getGenre() const {
	return m_genre;
}

std::string Book::getAuthor() const {
	return m_author;
}

const Tags_t& Book::getTags() const {
	return m_tags;
}

unsigned long Book::getISBN() const {
		return m_isbn;
}

void Book::print() const {
	std::cout << m_title << '\n'
			  << m_author << '\n'
			  << m_year << '\n'
			  << m_genre << '\n'
			  << m_description << '\n'
			  << m_rating << '\n'
			  << m_isbn << '\n';
	std::cout << '|';
	for(const char* t : m_tags) {
		std::cout << t << '|';
	}
	std::cout << '\n';
}