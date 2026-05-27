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
	std::string m_active_user;
	bool m_admin_logged_in;

	///void copyFrom() {
	///	///
	///}

	void free();

public:
	Library();
	Library(const Library&) = delete;				///
	Library& operator=(const Library&) = delete;	///
	~Library();

	void serialize() const;
	void deserialize();

	void login();
	void logout();
	bool loggedIn() const;
	bool loggedInAsAdmin() const;
	void usersAdd(User*);
	void usersRemove(std::string);

	void booksAdd(Book*);
	void booksRemove(unsigned long);
	void booksAll() const;
	void booksInfo(unsigned long) const;
	void booksFind(const Book::Option&, std::string) const;
	enum class Sort;
	void booksSort(const Book::Option&, const Sort&);
};