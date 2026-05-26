#include <string>
#include <iostream>
#include "Library.hpp"

Library::Library() : m_active_user() { m_users.push_back(new Admin{"admin", "i<3c++"}); }

void Library::free() {
	for (const User* u : m_users) {
		delete u;
	}
	
	for (const Book* b : m_books) {
		delete b;
	}

	m_active_user = "";
}

Library::~Library() {
	free();
}

void Library::serialize() const {
	
}

void Library::deserialize() {
	
}

void Library::login() {
///при въвеждане на паролата на екрана да се изписва символа * вместо реалния символ

///След въвеждането на командата потребителят последователно е питан 
///за потребителско име и парола. Ако потребител с посочените данни съществува 
///в програмата, се извежда съобщение “Welcome, <username>!”, където <username>
///съответства на  потребителското име. В противен случай се извежда съобщение 
///за грешно име или парола. При повторен опит за login, се изкарва съобщение “You are already logged in.”
}

void Library::logout() {
	m_active_user = "";
	std::cout << "Logged out.\n";
}

void Library::usersAdd(User* user) {
	std::string username{user->getUsername()};
	for (User* u : m_users) {
		if(u->getUsername() == username) {
			std::cout << "A user with that username already exists.\n";
			return;
		}
	}
	m_users.push_back(user);
	std::cout << "Added user " << username << '.' << '\n';
}

void Library::usersRemove(std::string username) {
	if(username=="admin") {
		std::cout << "Can't delete default admin user.\n";
		return;
	}

	for (int i = 0; i < m_users.size(); ++i) {
		if(m_users[i]->getUsername() == username) {
			m_users.erase(m_users.begin() + i);
			std::cout << "Deleted user " << username << '.' << '\n';
			return;
		}
	}
	std::cout << "No user with that username exists.\n";
}

void Library::booksAdd(Book* book) {
	for (const Book* b : m_books) {
		if(b->getISBN() == book->getISBN()) {
			std::cout << "A book with that ISBN already exists.\n";
			return;
		}
	}
	m_books.push_back(book);
	std::cout << "Added " << book->getTitle() << ".\n";
}

void Library::booksRemove(unsigned long isbn) {
	for (int i = 0; i < m_books.size(); ++i) {
		if(m_books[i]->getISBN() == isbn) {
			std::cout << "Removed " << m_books[i]->getTitle() << ".\n";
			m_books.erase(m_books.begin() + i);
			return;
		}
	}
	std::cout << "No book with that isbn exists.\n";
}

void Library::booksAll() const {
	for(const Book* b : m_books) {
		std::cout << b->getTitle() << '\n'
				  << b->getAuthor() << '\n'
				  << b->getGenre() << '\n'
				  << b->getISBN() << "\n\n";
	}
}

void Library::booksInfo(unsigned long isbn) const {
	for(const Book* b : m_books) {
		if (b->getISBN() == isbn) {
			b->print();
			return;
		}
	}
}

void Library::booksFind() const {
///Търсене на книга по зададен критерий да игнорира регистъра на буквите (малки или големи)
}

void Library::booksSort() {
///при сортиране на книгите по зададен критерий, да се напише алгоритъм различен от пряка селекция и метода на мехурчето
}