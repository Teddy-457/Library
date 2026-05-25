#pragma once
#include <vector>
#include <string>
#include "User.hpp"
#include "Admin.hpp"
#include "Book.hpp"
#include <iostream>////////////////

class Library {
private:
	std::vector<User*> m_users;
	std::vector<Book*> m_books;
	std::string m_active_user;

	void copyFrom() {
		///
	}

	void free();

public:
	Library();
	Library(const Library&) = delete;				///
	Library& operator=(const Library&) = delete;	///
	~Library() {
		std::cout << "destructor called\n";
		free();
	}

	void serialize() const;
	void deserialize();

	void login();
	void logout();
	void usersAdd(User*);
	void usersRemove(std::string);
	void booksAll() const;
	void booksInfo(unsigned) const;
	void booksFind() const;
	void booksSort();
};