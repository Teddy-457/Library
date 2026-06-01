#pragma once
#include <string>
#include <vector>

/// \enum BookOption
/// \brief Represents the available searchable and sortable fields for a Book.
enum class BookOption {
	TITLE,   ///< The title of the book.
	AUTHOR,  ///< The author of the book.
	TAG,     ///< A specific keyword tag associated with the book.
	YEAR,    ///< The publication year.
	RATING,  ///< The numerical rating of the book.
	INVALID = -1, ///< Indicates an invalid or unrecognized option.
};

/// \typedef Tags_t
/// \brief Alias for a collection of C-string tags associated with a book.
using Tags_t = std::vector<const char*>;

/// \class Book
/// \brief Represents a book in the library system.
///
/// Holds detailed metadata about a book, such as its title, author, genre, 
/// publication year, user ratings, and ISBN. Handles its own serialization 
/// and formatted console printing.
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

	/// \brief Safely deallocates the dynamically allocated tags.
	void free();

public:
	/// \brief The character used to separate fields when saving to a file.
	static constexpr char m_DELIMITER{ '%' };

	// Deleted default constructor and copy semantics
	Book() = delete;
	Book(const Book&) = delete;
	Book& operator=(const Book&) = delete;
	
	/// \brief Move constructor. Transfers resource ownership.
	/// \param other The Book to move data from.
	Book(Book&& other) noexcept;
	
	/// \brief Move assignment operator. Transfers resource ownership.
	/// \param other The Book to move data from.
	/// \return A reference to the assigned Book.
	Book& operator=(Book&& other) noexcept;
	
	/// \brief Destructor. Cleans up dynamically allocated tags.
	~Book();

	/// \brief Constructs a new Book with the given metadata.
	/// \param author The author of the book.
	/// \param title The title of the book.
	/// \param genre The genre of the book.
	/// \param description A short summary of the book.
	/// \param year The year of publication (Negative numbers are supported for BC dates).
	/// \param tags A collection of keyword tags indicating themes or topics.
	/// \param rating The numerical user rating of the book.
	/// \param isbn The unique International Standard Book Number.
	Book(std::string author, std::string title, std::string genre, std::string description, 
		 signed year, Tags_t tags, double rating, unsigned long isbn);

	/// \brief Serializes the book's data to a file.
	/// \param filename The path to the file where the book data should be appended.
	void serialize(const std::string& filename) const;
	
	/// \brief Deserializes a Book from a specific line in a data file.
	/// \param filename The path to the file to read from.
	/// \param line The line number (0-indexed or 1-indexed based on implementation) to parse.
	/// \return A dynamically allocated pointer to the newly created Book.
	/// \note The caller is responsible for deleting the returned Book instance.
	static Book* deserialize(const std::string& filename, unsigned line);

	/// \brief Prints a formatted representation of the book's metadata to the console.
	void print() const;

	/// \brief Retrieves the title.
	/// \return A constant reference to the book title.
	const std::string& getTitle() const;

	/// \brief Retrieves the genre.
	/// \return A constant reference to the book genre.
	const std::string& getGenre() const;

	/// \brief Retrieves the author.
	/// \return A constant reference to the book author.
	const std::string& getAuthor() const;

	/// \brief Retrieves the publication year.
	/// \return The signed year of publication.
	signed getYear() const;

	/// \brief Retrieves the user rating.
	/// \return The numerical rating.
	double getRating() const;

	/// \brief Retrieves the collection of tags.
	/// \return A constant reference to the vector of tags.
	const Tags_t& getTags() const;

	/// \brief Retrieves the ISBN.
	/// \return The ISBN identification number.
	unsigned long getISBN() const;

	/// \brief Converts a BookOption enum to its native string representation.
	/// \param option The BookOption to convert.
	/// \return A lowercase string matching the option command.
	static std::string optionToString(BookOption option);

	/// \brief Converts a string command to a BookOption enum.
	/// \param str The input string to parse.
	/// \return The corresponding BookOption, or BookOption::INVALID if the string form isn't recognized.
	static BookOption stringToOption(const std::string& str);
};