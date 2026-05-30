#pragma once
#include <string>
#include <vector>

enum class BookOption {
	TITLE,
	AUTHOR,
	TAG,
	YEAR,
	RATING,
	INVALID = -1,
};

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
	unsigned long m_isbn;

    static constexpr char m_DELIMITER{ '%' };

	void free();

public:
	Book(std::string, std::string, std::string, std::string, signed, Tags_t,
		 double, unsigned long);

	Book() = delete;
	Book(const Book&) = delete;
	Book& operator=(const Book&) = delete;
	Book (Book&&) noexcept;
	Book& operator=(Book&&) noexcept;
	~Book();

	void serialize(const std::string&) const;
	static Book* deserialize(const std::string&, unsigned);

	const std::string& getTitle() const;
	const std::string& getGenre() const;
	const std::string& getAuthor() const;
	signed getYear() const;
	double getRating() const;
	const Tags_t& getTags() const;
	unsigned long getISBN() const;
	static std::string optionToString(BookOption);
	static BookOption stringToOption(const std::string&);
	void print() const;
};