#pragma once
#include <string>
#include <vector>

using Tags_t = std::vector<const char*>;

class Book {
private:
	std::string m_author;
	std::string m_title;
	std::string m_genre;
	std::string m_description;
	signed m_year; //support for dates BC
	Tags_t m_tags;
	double m_rating;
	unsigned m_isbn;

public:
	Book(std::string author, std::string title, std::string genre,
		std::string description, signed year, Tags_t tags,
		double rating, unsigned isbn)
		: m_author(author), m_title(title), m_genre(genre)
		, m_description(description), m_year(year)
		, m_rating(rating), m_isbn(isbn)
	{
		for (const char* t : tags) {
			std::size_t size{ strlen(t) };
			char* tag = new char[size + 1];
			strcpy_s(tag, size+1, t);
			m_tags.push_back(tag);
		}
	}

	Book() = delete;
	Book(const Book&) = delete;
	Book& operator=(const Book&) = delete;

	~Book() {
		for (const char* t : m_tags) {
			delete[] t;
		}
	}

	void serialize(std::string) const;
	///static Book* deserialize(std::string, unsigned);
};