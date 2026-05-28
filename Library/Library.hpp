#pragma once
#include <vector>
#include <string>
#include "User.hpp"
#include "Admin.hpp"
#include "Book.hpp"

class Library {
private:
	std::vector<User*> m_users;
	std::vector<Book*> m_books;

	std::string m_filename;
	
	std::string m_active_user;
	bool m_admin_logged_in;

    const std::string m_default_admin_password{ "i<3c++" };
	
	void serialize(const std::string&) const;
	void deserialize(const std::string&);
	
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
    void save();
    void saveas(const std::string&);

	void login(const std::string&, const std::string&);
	void logout();
	bool loggedIn() const;
	bool loggedInAsAdmin() const;
	void usersAdd(User*);
	void usersRemove(const std::string&);

	void booksAdd(Book*);
	void booksRemove(unsigned long);
	void booksAll() const;
	void booksInfo(unsigned long) const;
	void booksFind(const Book::Option&, std::string) const;
	enum class Sort;
	void booksSort(const Book::Option&, const Sort&);
};