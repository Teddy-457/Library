#include <iostream>
#include <string>
#include <fstream>
#include "Book.hpp"
#include "Utilities.hpp"

Book::Book(std::string author, std::string title, std::string genre,
		std::string description, signed year, Tags_t tags,
		double rating, unsigned long isbn)
		: m_author(author), m_title(title), m_genre(genre)
		, m_description(description), m_year(year)
		, m_rating(rating), m_isbn(isbn)
	{
		for (const char* t : tags) {
			std::size_t size{ strlen(t) };
			char* tag = new char[size + 1];
			strcpy_s(tag, size + 1, t);
			m_tags.push_back(tag);
		}
	}

Book::Book(Book&& other) noexcept {
	m_author = std::move(other.m_author);
	m_title = std::move(other.m_title);
	m_genre = std::move(other.m_genre);
	m_description = std::move(other.m_description);
	m_year = other.m_year;
	m_tags = std::move(other.m_tags);
	m_rating = other.m_rating;
	m_isbn = other.m_isbn;
}

Book& Book::operator=(Book&& other) noexcept {
	if (this != &other) {
		free();

		m_author = std::move(other.m_author);
		m_title = std::move(other.m_title);
		m_genre = std::move(other.m_genre);
		m_description = std::move(other.m_description);
		m_year = other.m_year;
		m_tags = std::move(other.m_tags);
		m_rating = other.m_rating;
		m_isbn = other.m_isbn;

		other.m_tags.clear();
	}
	return *this;
}

void Book::free() {
	for (const char* t : m_tags) {
		delete[] t;
	}
	m_tags.clear();
}

Book::~Book() {
	free();
}

void Book::serialize(const std::string& filename) const {
	std::ofstream file(filename, std::ios::app);
	Utilities::checkIfOpen(file);
	file << m_DELIMITER << m_isbn << m_DELIMITER << m_rating << m_DELIMITER << m_year << m_DELIMITER << m_description << m_DELIMITER << m_genre << m_DELIMITER << m_title << m_DELIMITER << m_author << m_DELIMITER;
	for(const char* t : m_tags) {
		file << t << m_DELIMITER;
	}
	file << '\n'; file.close();
}

Book* Book::deserialize(const std::string& filename, unsigned line) {
	std::ifstream file(filename, std::ios::in);
	Utilities::checkIfOpen(file);

	Utilities::skipLines(file, line);

    char check = file.get();
    if (check == m_DELIMITER) {
		unsigned long isbn;
		double rating;
		signed year;
		std::string description, genre, title, author;
		Tags_t tags;

		file >> isbn;
		file.ignore(1);
		file >> rating;
		file.ignore(1);
		file >> year;
		file.ignore(1);

		char c = file.get();
		while (c != m_DELIMITER) {
			description.push_back(c);
			c = file.get();
		}
		c = file.get();
		while (c != m_DELIMITER) {
			genre.push_back(c);
			c = file.get();
		}
		c = file.get();
		while (c != m_DELIMITER) {
			title.push_back(c);
			c = file.get();
		}
		c = file.get();
		while (c != m_DELIMITER && c != '\n') {
			author.push_back(c);
			c = file.get();
		}
		
		while(c != '\n') {
			c = file.get();

			std::string temp_tag;
			while (c != m_DELIMITER && c != '\n') {
				temp_tag.push_back(c);
				c = file.get();
			}
			if(c != '\n') {
				char* tag = new char[temp_tag.size() + 1];
				strcpy_s(tag, temp_tag.size()+1, temp_tag.c_str());
				tags.push_back(tag);
			}
		}
		file.close();

		return new Book{author, title, genre,
						description, year, std::move(tags),
						rating, isbn};
	}
	else {
		file.close();
		Utilities::logAndThrow("Tried to deserialize a user in place of a book");
	}
}

const std::string& Book::getTitle() const {
	return m_title;
}

const std::string& Book::getGenre() const {
	return m_genre;
}

const std::string& Book::getAuthor() const {
	return m_author;
}

signed Book::getYear() const {
	return m_year;
}

double Book::getRating() const {
	return m_rating;
}

const Tags_t& Book::getTags() const {
	return m_tags;
}

unsigned long Book::getISBN() const {
		return m_isbn;
}

std::string Book::optionToString(BookOption option) {
	switch (option) {
		case BookOption::TITLE:
			return "title";
		case BookOption::AUTHOR:
			return "author";
		case BookOption::TAG:
			return "tag";
		case BookOption::YEAR:
			return "year";
		case BookOption::RATING:
			return "rating";
		case BookOption::INVALID:
			return "";
		default:
			Utilities::logAndThrow("No such BookOption exists");
	}
}

BookOption Book::stringToOption(const std::string& option) {
	if (option == "title") {
		return BookOption::TITLE;
	}
	else if (option == "author") {
		return BookOption::AUTHOR;
	}
	else if (option == "tag") {
		return BookOption::TAG;
	}
	else if (option == "year") {
		return BookOption::YEAR;
	}
	else if (option == "rating") {
		return BookOption::RATING;
	}
	else {
		return BookOption::INVALID;
	}
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
}