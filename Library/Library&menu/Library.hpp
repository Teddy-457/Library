#pragma once
#include <vector>
#include <string>
#include "../User/Admin.hpp"
#include "../User/User.hpp"
#include "../Book.hpp"

/// \enum Logging
/// \brief Represents the verbosity level of console output.
enum class Logging {
	QUIET,    ///< No extra informational output.
	VERBOSE,  ///< Standard informational output for actions.
	DEBUG,    ///< Detailed debug traces (e.g., function execution paths).
};

/// \enum BookSort
/// \brief Defines the sorting order when querying books.
enum class BookSort {
	ASCENDING,   ///< Sort elements in ascending order (A-Z, lowest to highest).
	DESCENDING,  ///< Sort elements in descending order (Z-A, highest to lowest).
	INVALID = -1,///< Indicates an invalid or unrecognized sort order.
};

/// \class Library
/// \brief The central manager for the library application.
///
/// Handles database file operations (open, save, load), active user sessions, 
/// and maintains the in-memory collections of users and books. It enforces 
/// logging levels and routes specific queries and commands.
class Library {
private:
	std::vector<User*> m_users;
	std::vector<Book*> m_books;

	std::string m_filename;
	
	std::string m_active_user;
	bool m_admin_logged_in;

    const std::string m_default_admin_password{ "i<3c++" };
	const Logging m_LOG_LEVEL{ Logging::VERBOSE };
	
	/// \brief Serializes the library state (users and books) to a file.
	void serialize(const std::string&) const;
	
	/// \brief Deserializes the library state from a file into memory.
	void deserialize(const std::string&);

	/// \brief Helper functions to find a book by specific criteria.
	bool findBookByTitle(const std::string&) const;
	bool findBookByAuthor(const std::string&) const;
	bool findBookByTag(const std::string&) const;
	
	/// \brief Clears all dynamically allocated users and books and resets the library state.
	void free();

public:
	/// \brief Default constructor. Initializes an empty library with a default admin user.
	Library();

	// Deleted copying and moving semantics to keep the Library uniquely bound to one system.
	Library(const Library&) = delete;
	Library& operator=(const Library&) = delete;
	Library (Library&&) noexcept = delete;
	Library& operator=(Library&&) noexcept = delete;

	/// \brief Destructor. Calls free() to release all allocated resources.
	~Library();
	
	/// \brief Opens a file directly, loading its users and books into memory.
	/// \param filename The name of the file to open. Creates it if it doesn't exist.
	void open(const std::string& filename);
    
	/// \brief Closes the currently active library file, clearing the internal memory.
	void close();
    
	/// \brief Saves the current in-memory library state back to the active file.
	void save() const;

	/// \brief Saves the library state to a specific file.
	/// \param filename The destination file.
	/// \param called_from_save Internal flag to suppress success output if called from save().
	/// \return True if successful, false otherwise.
	bool saveas(const std::string& filename, bool called_from_save = false) const;

	/// \brief Authenticates a user and starts an active session.
	/// \param username The account to log in to.
	/// \param password The plain-text password to verify against.
	void login(const std::string& username, const std::string& password);

	/// \brief Logs out the currently active user.
	void logout();

	/// \brief Adds a user to the library.
	/// \param user A dynamically allocated user to add. Ownership is transferred to Library.
	void usersAdd(User* user);

	/// \brief Removes a user by their username.
	/// \param username The exact username of the user to delete.
	void usersRemove(const std::string& username);

	/// \brief Adds a new book to the library.
	/// \param book A dynamically allocated book to add. Ownership is transferred to Library.
	void booksAdd(Book* book);

	/// \brief Removes a book from the library via its ISBN.
	/// \param isbn The unique ISBN of the book to remove.
	void booksRemove(unsigned long isbn);

	/// \brief Prints a formatted list of all books in the library.
	void booksAll() const;

	/// \brief Prints detailed information for a specific book.
	/// \param isbn The ISBN of the book to query.
	void booksInfo(unsigned long isbn) const;

	/// \brief Queries and prints books matching a specified option and value.
	/// \param option The field to search (e.g., TITLE, AUTHOR, TAG).
	/// \param value The query string to match.
	void booksFind(BookOption option, std::string value) const;

	/// \brief Sorts the internal collection of books and outputs the sorted view.
	/// \param option The field to sort by.
	/// \param sort The direction to sort (ASCENDING or DESCENDING).
	void booksSort(BookOption option, BookSort sort);

	/// \brief Checks if there is an active valid user session.
	/// \return True if a user is logged in, false otherwise.
	bool loggedIn() const;

	/// \brief Checks if the currently active user has administrator privileges.
	/// \return True if the user is logged in and is an admin.
	bool loggedInAsAdmin() const;

	/// \brief Checks if a database file is currently opened and loaded in memory.
	/// \return True if an active file exists.
	bool activeFile() const;

	/// \brief Gets the current logging verbosity level of the library.
	/// \return The active Logging configuration.
	Logging getLogLevel() const;

	/// \brief Converts a BookSort enum to a readable lowercase string.
	/// \param sort The BookSort enum.
	/// \return "ascending" or "descending".
	static std::string sortToString(BookSort sort);

	/// \brief Converts an input string command to a BookSort enum.
	/// \param str The input string (e.g. "asc", "desc").
	/// \return The matching BookSort, or BookSort::INVALID.
	static BookSort stringToSort(const std::string& str);
};