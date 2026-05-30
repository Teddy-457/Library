#pragma once
#include <vector>
#include <string>
#include "../User/Admin.hpp"
#include "../User/User.hpp"
#include "../Book.hpp"

enum class Logging {
	QUIET,
	VERBOSE,
	DEBUG,
};

enum class BookSort {
	ASCENDING,
	DESCENDING,
	INVALID = -1,
};

class Library {
private:
	std::vector<User*> m_users;
	std::vector<Book*> m_books;

	std::string m_filename;
	
	std::string m_active_user;
	bool m_admin_logged_in;

    const std::string m_default_admin_password{ "i<3c++" };
	const Logging m_LOG_LEVEL{ Logging::VERBOSE };
	
	void serialize(const std::string&) const;
	void deserialize(const std::string&);

	bool findBookByTitle(const std::string&) const;
	bool findBookByAuthor(const std::string&) const;
	bool findBookByTag(const std::string&) const;
	
	void free();

public:
	Library();
	Library(const Library&) = delete;
	Library& operator=(const Library&) = delete;
	Library (Library&&) noexcept = delete;
	Library& operator=(Library&&) noexcept = delete;
	~Library();
	
	void open(const std::string&);
    void close();
    void save() const;
	void saveas(const std::string&, bool = false) const;

	void login(const std::string&, const std::string&);
	void logout();
	bool loggedIn() const;
	bool loggedInAsAdmin() const;
	bool activeFile() const;
	Logging getLogLevel() const;
	void usersAdd(User*);
	void usersRemove(const std::string&);

	void booksAdd(Book*);
	void booksRemove(unsigned long);
	void booksAll() const;
	void booksInfo(unsigned long) const;
	void booksFind(BookOption, std::string) const;
	void booksSort(BookOption, BookSort);

	static std::string sortToString(BookSort);
	static BookSort stringToSort(const std::string&);
};